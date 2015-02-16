#include	<boost/test/unit_test.hpp>

#include	"corniflex/EventManager.hh"
#include	"corniflex/Event.hh"
#include	<iostream>

class		FakeEvent1 : public corniflex::Event {
public:
  int	_id = 42;
  int getID() { return (_id); }
};

class		FakeEvent2 : public corniflex::Event {
public:
  int	_id = 10;
  int getID() { return (_id); }
};

class		FakeSystem {
public:
  void		function(corniflex::Event *) {}
};

BOOST_AUTO_TEST_SUITE(EventManagerTesting)

BOOST_AUTO_TEST_CASE(EventManagerTestHandlers)
{
  corniflex::EventManager	manager;
  FakeSystem			system;

  manager.setSynchronous(true);
  manager.addHandler(FakeEvent1(), std::bind(&FakeSystem::function, &system, std::placeholders::_1));
  BOOST_CHECK(manager.hasHandler(FakeEvent1()));
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 1);
  manager.addHandler(FakeEvent1(), [] (corniflex::Event *) {});
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 3);
  manager.addHandler(FakeEvent2(), nullptr);
  BOOST_CHECK(manager.hasHandler(FakeEvent2()));
}

BOOST_AUTO_TEST_CASE(EventManagerTestAsynchronous)
{
  corniflex::EventManager	manager;

  manager.setSynchronous(false);
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 0);
  manager.addHandler(FakeEvent1(), [] (corniflex::Event *) {});
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 0);
  manager.processLastEvent();
  BOOST_CHECK(manager.getNbProcessedEvent() == 1);
  manager.processLastEvent();
  BOOST_CHECK(manager.getNbProcessedEvent() == 2);
}

BOOST_AUTO_TEST_CASE(EventManagerTestCallback)
{
  corniflex::EventManager	manager;

  bool	b = false;
  manager.setSynchronous(true);
  manager.sendEvent(new FakeEvent1(), [] (corniflex::Event *) {
    BOOST_FAIL("Should not call calback");
  });
  manager.addHandler(FakeEvent1(), [] (corniflex::Event *) {
  });
  manager.sendEvent(new FakeEvent1(), [&b] (corniflex::Event *) {
    b = true;
  });
  BOOST_CHECK(b);
}

BOOST_AUTO_TEST_CASE(EventManagerTestEventsType)
{
  corniflex::EventManager	manager;

  manager.setSynchronous(true);
  manager.addHandler(FakeEvent1(), [] (corniflex::Event *e) {
    BOOST_CHECK(dynamic_cast<FakeEvent1 *>(e) != NULL);
  });
  manager.addHandler(FakeEvent2(), [] (corniflex::Event *e) {
    BOOST_CHECK(dynamic_cast<FakeEvent1 *>(e) == NULL);
  });

  manager.sendEvent(new FakeEvent1());
  manager.sendEvent(new FakeEvent2());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(EventManagerTestHandlersRemoval)
{
  corniflex::EventManager	manager;
  FakeSystem			system;

  manager.setSynchronous(true);
  manager.addHandler(FakeEvent1(), std::bind(&FakeSystem::function, &system, std::placeholders::_1));
  manager.removeHandlers(FakeEvent1());
  manager.sendEvent(new FakeEvent1());
  manager.addHandler(FakeEvent1(), [] (corniflex::Event *) {});
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 1);
  manager.removeHandlers(FakeEvent1());
  manager.sendEvent(new FakeEvent1());
  BOOST_CHECK(manager.getNbProcessedEvent() == 1);
}
