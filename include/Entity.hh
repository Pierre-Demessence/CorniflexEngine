#pragma once

#include "ComponentManager.hh"

namespace corniflex {

class Entity {
private:
  static long long int _nextID;
  int	_id;

  ComponentManager	componentManager;

public:
  Entity();

  long long int	getID() const;

};

}
