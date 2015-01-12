#pragma once

#include "EventManager.hpp"
#include "SceneManager.hh"
#include "SystemManager.hh"

namespace corniflex {

class Engine {
private:
  EventManager<System> _eventManager;
  SceneManager _sceneManager;
  SystemManager _systemManager;

public:
  Engine();

};

}
