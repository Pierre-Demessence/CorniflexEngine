#pragma once

#include "EventManager.hh"
#include "SceneManager.hh"
#include "SystemManager.hh"

namespace corniflex {

class Engine {
private:
  EventManager	_eventManager;
  SceneManager	_sceneManager;
  SystemManager	_systemManager;

public:
  Engine();

};

}
