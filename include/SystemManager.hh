#pragma once

#include <vector>

#include "System.hh"

namespace corniflex {

class SystemManager {
private:
  std::vector<System *>	_systems;

public:
  void	add(System *);
  void	remove();
};

}
