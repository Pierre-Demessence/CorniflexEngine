#include "EventManager.hh"

// ----- ----- Getters ----- ----- //

unsigned long long	corniflex::EventManager::getNbProcessedEvent() const
{
  return (this->_nbProcessedEvent);
}

// ----- ----- Public Members ----- ----- //

bool		corniflex::EventManager::hasHandler(const Event &event) {
  this->_mutexHandlers.lock();
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  return (it != this->_eventHandlers.end());
  this->_mutexHandlers.unlock();
}

void		corniflex::EventManager::addHandler(const Event &event, t_handler handler)
{
  this->_mutexHandlers.lock();
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  if (it != this->_eventHandlers.end()) {
    it->second.push_back(handler);
    return ;
  }
  this->_eventHandlers[typeid(event)].push_back(handler);
  this->_mutexHandlers.unlock();
}

void		corniflex::EventManager::sendEvent(Event *event, t_fptr func) {
  this->_mutexEvents.lock();
  this->_events.push_back(std::make_pair(event, func));
  if (this->_synchronous)
    this->processLastEvent();
  this->_mutexEvents.unlock();
}

void		corniflex::EventManager::processLastEvent() {
  if (this->_events.size() == 0)
    return ;
  this->_mutexEvents.lock();
  Event *event = this->_events.back().first;
  t_fptr func = this->_events.back().second;
  this->_events.erase(this->_events.end());
  processEvent(event, func);
  this->_mutexEvents.unlock();
}

void		corniflex::EventManager::processFirstEvent() {
  if (this->_events.size() == 0)
    return ;
  this->_mutexEvents.lock();
  Event *event = this->_events.front().first;
  t_fptr func = this->_events.front().second;
  this->_events.erase(this->_events.begin());
  processEvent(event, func);
  this->_mutexEvents.unlock();
}

void		corniflex::EventManager::setSynchronous(bool synchronous) {
  this->_synchronous = synchronous;
}

// ----- ----- Private Members ----- ----- //

void		corniflex::EventManager::processEvent(Event *event, t_fptr func) {
  unsigned long long	oldnb = this->_nbProcessedEvent;
  auto it = this->_eventHandlers.find(std::type_index(typeid(*event)));
  if (it != this->_eventHandlers.end()) {
    for (auto itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
      ++_nbProcessedEvent;
      (*itSecond)(event);
    }
  }
  if (this->_nbProcessedEvent > oldnb && func)
    func(event);
  delete event;
}
