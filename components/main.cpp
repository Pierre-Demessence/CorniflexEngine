#include <iostream>
#include <sstream>
#include "AttributeContainer.hpp"
#include "AttributeExecuterLeftRedirect.hpp"
#include "AttributeRegistrer.hpp"
#include "Component.hpp"

// template <const char *test>
// class Test
// {
// public:
//   constexpr static const char *value = test;
// };

// constexpr long __get_str(const char *x)
// {
//   return (485);
// }

// #define HASH(x) Test<__get_str(x)>()

int	main()
{
  // int				b(54564);
  // int				c(424242);
  // AttributeContainer<int>	a(b);
  // AttributeContainer<int>	d(c);

  // std::string g = "default";
  // AttributeContainer<std::string>	f(g);
  // f.addAttributeExecuter<std::string, AttributeExecuterLeftRedirect, std::ostream>();

  // std::cout << f.get<std::string>() << std::endl;
  // f.set<std::string>("bonjour :)");
  // f.apply(std::cout);
  // std::cout << std::endl;
  // std::string tmp = "zerij";
  // f.set<std::string>(tmp);
  // f.apply(std::cout);

  // a.addAttributeExecuter<int, AttributeExecuterLeftRedirect, std::ostream>();
  // a.addAttributeExecuter<int, AttributeExecuterLeftRedirect, std::ostringstream>();
  // std::cout << "54564 = " << a.get<int>() << std::endl;
  // a.set(12);
  // a.apply(std::cout);
  // std::cout << std::endl;
  // a.set(d);
  // std::cout << a.get<int>() << std::endl;

  // std::ostringstream	oss;
  // oss << "Coucou: ";
  // a.apply(oss);
  // std::cout << oss.str() << std::endl;

  // std::cout << Test<"coucou">::value << std::endl;

  Component comp;
  int value = 89451;

  comp.registerAttribute<int,
  			 AttributeExecuterLeftRedirect, std::ostream,
  			 AttributeExecuterLeftRedirect, std::ostringstream>(value);


  std::cout << "Test std::cout" << std::endl;
  comp.getAttributes().front()->apply(std::cout);
  std::cout << std::endl << std::endl;

  std::cout << "Test std::ostringstream" << std::endl;
  std::ostringstream	oss;

  oss << "Coucou: ";
  comp.getAttributes().front()->apply(oss);
  std::cout << oss.str() << std::endl;
  return (0);
}
