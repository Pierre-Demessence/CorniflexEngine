#ifndef _TEST_H_
# define _TEST_H_

# include	<map>
# include	<string>

# include	<boost/any.hpp>

class		Component
{
protected:
  std::string	_type;

public:
  std::map<std::string, boost::any>	_fields;

public:
  Component();
  Component(const std::string &type);
};

#endif /* _TEST_H_ */
