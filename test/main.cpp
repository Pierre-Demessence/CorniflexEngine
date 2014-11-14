#include	<iostream>
#include	<string>

#include	<boost/any.hpp>

#include	"Component.hh"

int		main()
{
  Component	c("test");
  
  c._fields["x"] = 42;
  c._fields["y"] = 123;
  c._fields["name"] = std::string("Foo");
  
  std::cout << boost::any_cast<std::string>(c._fields["name"]) << " : (" << boost::any_cast<int>(c._fields["x"]) << ";" << boost::any_cast<int>(c._fields["y"]) << ")" << std::endl;
  return (0);
}
