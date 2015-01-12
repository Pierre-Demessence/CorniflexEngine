#pragma once

# include	<map>
# include	<string>
# include	<type_traits>

# include	<boost/any.hpp>

namespace corniflex {

class		Component
{
private:
std::string	_type;
std::map<std::string, boost::any>	_fields;

public:
Component(const std::string &type);

void	set(const std::string &key, boost::any value);
template<typename T>
  T	get(const std::string &key) const;

};

}

template<typename T>
T	corniflex::Component::get(const std::string &key) const
{
  try
    {
      return (boost::any_cast<T>(this->_fields.at(key)));
    }
  catch(boost::bad_any_cast& ex)
    {
      return (0);
    }
}
