#pragma once

#include <functional>
#include <map>
#include <mutex>
#include <typeindex>
#include <vector>

#include "Event.hh"

namespace corniflex {

//typedef void (*)(Event *) t_fptr;
typedef std::function<void(Event *)> t_fptr;

template <typename T>
class EventManager {
private:
  std::map<std::type_index, std::vector<std::pair<T *, void (T::*)(Event *)> > >	_eventHandlers;
  std::vector<std::pair<Event*, t_fptr > >	_events;
  std::mutex	_mutexHandlers;
  std::mutex	_mutexEvents;
  bool		_synchronous = false;

public:
  EventManager() {}

  virtual	~EventManager() {}

  bool		hasHandler(const Event &event) const {
    this->_mutexHandlers.lock();
    auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
    return (it != this->_eventHandlers.end());
    this->_mutexHandlers.unlock();
  }

  void		addHandler(const Event &event, T *obj, void (T::*e)(Event *))
  {
    this->_mutexHandlers.lock();
    auto it = this->_eventHandlers.find(std::type_index(typeid(event)));
    if (it != this->_eventHandlers.end()) {
      auto itSecond = it->second.begin();
      for (itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
	if (itSecond->second == e)
	  return ;
      }
      it->second.push_back(std::make_pair(obj, e));
      return ;
    }
    this->_eventHandlers[std::type_index(typeid(event))].push_back(std::make_pair(obj, e));
    this->_mutexHandlers.unlock();
  }

  void		sendEvent(Event *event, void (*func)(Event *)) {
    this->_mutexEvents.lock();
    this->_events.push_back(std::make_pair(event, func));
    this->_mutexEvents.unlock();
    if (this->_synchronous)
      this->processLastEvent();
  }

  void		processLastEvent() {
    if (this->_events.size() == 0)
      return ;
    this->_mutexEvents.lock();
    Event *event = this->_events.back().first;
    t_fptr func = this->_events.back().second;
    this->_events.erase(this->_events.end());
    this->_mutexEvents.unlock();
    processEvent(event, func);
  }

  void		processFirstEvent() {
    if (this->_events.size() == 0)
      return ;
    this->_mutexEvents.lock();
    Event *event = this->_events.front().first;
    t_fptr func = this->_events.front().second;
    this->_events.erase(this->_events.begin());
    this->_mutexEvents.unlock();
    processEvent(event, func);
  }

  void		setSynchronous(bool synchronous) {
    this->_synchronous = synchronous;
  }

private:
  void		processEvent(Event *event, t_fptr func) {
    unsigned int	i = 0;
    this->_mutexHandlers.lock();
    auto it = this->_eventHandlers.find(std::type_index(typeid(*event)));
    if (it != this->_eventHandlers.end()) {
      for (auto itSecond = it->second.begin(); itSecond != it->second.end(); ++itSecond) {
	++i;
	((itSecond->first)->*((itSecond->second)))(event);
      }
    }
    this->_mutexHandlers.unlock();
    if (i > 0 && func)
      func(event);
    delete event;
  }

};

}
