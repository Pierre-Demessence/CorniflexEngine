#include <algorithm>
#include <mutex>

#include "EventManager.hh"

// ----- ----- Getters ----- ----- //

unsigned long long	corniflex::EventManager::getNbProcessedEvent() const {
  std::lock_guard<std::mutex> lock(this->_mutexEvents);
  return (this->_nbProcessedEvent);
}

// ----- ----- Public Members ----- ----- //

bool		corniflex::EventManager::hasHandler(const Event &event) const {
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  return (it != this->_eventHandlers.end());
}

unsigned int		corniflex::EventManager::countHandlers(const Event &event) const {
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  if (it != this->_eventHandlers.end())
    return (it->second.size());
  return (0);
}

void		corniflex::EventManager::addHandler(const Event &event, t_handlerptr handler)
{
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  if (it != this->_eventHandlers.end())
    it->second.push_back(handler);
  else {
    this->_eventHandlers[typeid(event)].push_back(handler);
  }
}
#include <iostream>
void		corniflex::EventManager::removeHandler(const Event &event, t_handlerptr handler) {
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  if (it != this->_eventHandlers.end())
    it->second.erase(std::remove(it->second.begin(), it->second.end(), handler));
}

void		corniflex::EventManager::clearHandlers(const Event &event) {
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  if (!this->hasHandler(event))
    return ;
  auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
  if (it != this->_eventHandlers.end()) {
    it->second.clear();
  }
}

void		corniflex::EventManager::sendEvent(Event *event, t_callback func) {
  std::lock_guard<std::mutex> lock(this->_mutexEvents);
  this->_events.push_back(std::make_pair(event, func));
  if (this->_synchronous)
    this->processLastEvent();
}

void		corniflex::EventManager::processLastEvent() {
  std::lock_guard<std::mutex> lock(this->_mutexEvents);
  if (this->_events.size() == 0)
    return ;
  Event *event = this->_events.back().first;
  t_callback func = this->_events.back().second;
  this->_events.erase(this->_events.end());
  processEvent(event, func);
}

void		corniflex::EventManager::processFirstEvent() {
  std::lock_guard<std::mutex> lock(this->_mutexEvents);
  if (this->_events.size() == 0)
    return ;
  Event *event = this->_events.front().first;
  t_callback func = this->_events.front().second;
  this->_events.erase(this->_events.begin());
  processEvent(event, func);
}

void		corniflex::EventManager::setSynchronous(bool synchronous) {
  std::lock_guard<std::mutex> lock(this->_mutexHandlers);
  this->_synchronous = synchronous;
}

// ----- ----- Private Members ----- ----- //

void		corniflex::EventManager::processEvent(Event *event, t_callback func) {
  unsigned long long	oldnb = this->_nbProcessedEvent;
  auto it = this->_eventHandlers.find(std::type_index(typeid(*event)));
  if (it != this->_eventHandlers.end()) {
    for (auto itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
      ++_nbProcessedEvent;
      (*(*itSecond))(event);
    }
  }
  if (this->_nbProcessedEvent > oldnb && func)
    func(event);
  delete event;
}

// ----- ----- Static Methods ----- ----- //

corniflex::t_handlerptr	corniflex::EventManager::makeHandler(t_handler handler) {
  return (std::make_shared<t_handler>(handler));
}
