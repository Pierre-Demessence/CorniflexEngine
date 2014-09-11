#include	<algorithm>
#include	<iostream>

#include	"Object.hpp"
#include	"SettingsManager.hh"

int	main()
{
  // WTF is this thing ?
  /*
  Integer i = Integer(10);
  std::cout << i << std::endl;
  i.value() = 42;
  std::cout << i << std::endl;
  i = 9000;
  std::cout << i << std::endl;

  String s = String("toto");
  std::cout << s << std::endl;
  return (0);
  */

  SettingsManager *settings = new SettingsManager("settings.conf");

  /*
  std::cout << settings->exist("toto") << std::endl;
  settings->set("toto", "42");
  std::cout << settings->exist("toto") << std::endl;
  std::cout << settings->check("toto", "43") << std::endl;
  std::cout << settings->check("toto", "42") << std::endl;
  */

  if (settings->check("greet", "1"))
    std::cout << "SALUT!" << std::endl;
   
  delete settings;
}
