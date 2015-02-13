#include	<boost/test/unit_test.hpp>

#include	"corniflex/EventManager.hh"
#include	"corniflex/Event.hh"
#include	<iostream>

class		FakeSystem {
public:
  void		function(corniflex::Event *e) {
    (void)e;
    std::cout << "FakeSystem Event Handler" << std::endl;
  }
};

class		FakeEvent : public corniflex::Event
{

};

BOOST_AUTO_TEST_SUITE(EventManagerTesting)

BOOST_AUTO_TEST_CASE(EventManagerTest)
{
  corniflex::EventManager	manager;
  FakeSystem			system;

  manager.addHandler(corniflex::Event(), std::bind(&FakeSystem::function, &system, std::placeholders::_1));
  manager.addHandler(corniflex::Event(), [] (corniflex::Event *e) {
    (void)e;
    std::cout << "Lambda Event Handler" << std::endl;
  });
  manager.addHandler(FakeEvent(), [] (corniflex::Event *e) {
    (void)e;
    std::cout << "Lambda FakeEvent Handler" << std::endl;
  });
  manager.setSynchronous(true);
  std::cout << "Event Fired" << std::endl;
  manager.sendEvent(new corniflex::Event(), [] (corniflex::Event *e) {
    (void)e;
    std::cout << "Event Callback" << std::endl;
  });
  std::cout << "FakeEvent Fired" << std::endl;
  manager.sendEvent(new FakeEvent(), [] (corniflex::Event *e) {
    (void)e;
    std::cout << "FakeEvent Callback" << std::endl;
  });
  manager.processFirstEvent();
  manager.processFirstEvent();
  manager.processFirstEvent();
}

BOOST_AUTO_TEST_SUITE_END()
