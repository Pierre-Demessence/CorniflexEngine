#include	<boost/test/unit_test.hpp>

#include	"corniflex/EventManager.hpp"
#include	"corniflex/Event.hh"
#include	<iostream>

class	FakeSystem {
public:
  void		function(corniflex::Event *e) {
    (void)e;
    std::cout << "YO" << std::endl;
  }
};

BOOST_AUTO_TEST_SUITE(EventManagerTesting)

BOOST_AUTO_TEST_CASE(EventManagerTest)
{
  FakeSystem	system;
  corniflex::EventManager<FakeSystem>	manager;

  manager.addHandler(corniflex::Event(), &system, &FakeSystem::function);
  manager.setSynchronous(true);
  manager.sendEvent(new corniflex::Event(), [] (corniflex::Event *e) {
    (void)e;
    std::cout << "YEH" << std::endl;
  });
  std::cout << "ti" << std::endl;
  manager.processFirstEvent();
  manager.processFirstEvent();
  manager.processFirstEvent();
}

BOOST_AUTO_TEST_SUITE_END()
