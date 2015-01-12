#include "Entity.hh"

long long int corniflex::Entity::_nextID = 1;

corniflex::Entity::Entity() {
  this->_id = Entity::_nextID++;
}

long long int	corniflex::Entity::getID() const {
  return (this->_id);
}
