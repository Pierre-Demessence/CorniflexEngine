#pragma once

# include	<map>
# include	<string>
# include	<type_traits>

# include	<boost/variant.hpp>

namespace corniflex {

class		Component;

typedef boost::variant<char, int, long, long long, float, double, std::string, bool, Component*> t_variantTypes;

class		Component
{
private:
  std::string	_type;
  std::map<std::string, t_variantTypes>	_fields;

public:
  Component(const std::string &type);

  void	set(const std::string &key, t_variantTypes value);
  template<typename T>
  T	get(const std::string &key) const;
};

}

template<typename T>
T	corniflex::Component::get(const std::string &key) const
{
  try
    {
      return (boost::get<T>(this->_fields.at(key)));
    }
  catch(boost::bad_get& ex)
    {
      return (0);
    }
}
