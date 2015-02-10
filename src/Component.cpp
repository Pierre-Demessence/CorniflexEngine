#include "Component.hpp"

corniflex::Component::Component(const std::string &type)
{
  this->_type = type;
}

void	corniflex::Component::set(const std::string &key, t_variantTypes value)
{
  this->_fields[key] = value;
}
