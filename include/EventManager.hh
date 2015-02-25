#pragma once

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <typeindex>
#include <vector>

#include "Event.hh"

namespace corniflex {

typedef std::function<void(Event *)>	t_handler;
typedef std::shared_ptr<t_handler>	t_handlerptr;
typedef std::function<void(Event *)>	t_callback;

class EventManager {

private:
  std::map<std::type_index, std::vector<t_handlerptr > >	_eventHandlers;
  std::vector<std::pair<Event*, t_callback > >		_events;
  mutable std::mutex	_mutexHandlers;
  mutable std::mutex	_mutexEvents;
  bool		_synchronous = false;

  unsigned long long	_nbProcessedEvent = 0;

public:
  // ----- ----- Getters ----- ----- //
  unsigned long long	getNbProcessedEvent() const;

  // ----- ----- Public Members ----- ----- //
  bool		hasHandler(const Event &event) const;
  unsigned int	countHandlers(const Event &event) const;
  void		addHandler(const Event &event, t_handlerptr handler);
  void		removeHandler(const Event &event, t_handlerptr handler);
  void		clearHandlers(const Event &event);
  void		sendEvent(Event *event, t_callback func = nullptr);
  void		processLastEvent();
  void		processFirstEvent();
  void		setSynchronous(bool synchronous);

private:
  // ----- ----- Private Members ----- ----- //
  void		processEvent(Event *event, t_callback func);

  // ----- ----- Static Methods ----- ----- //
public:
  static t_handlerptr	makeHandler(t_handler handler);
};

}
