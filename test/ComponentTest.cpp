#include	<boost/test/unit_test.hpp>

#include	"corniflex/Component.hpp"

BOOST_AUTO_TEST_SUITE(ComponentTesting)

BOOST_AUTO_TEST_CASE(ComponentCreationTest)
{
  corniflex::Component	a("test");
  BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(ComponentFieldsTest)
{
  corniflex::Component	a("test");

  a.set("a", 200);
  a.set("b", 3.14f);
  a.set("c", std::string("foo"));
  a.set("d", new corniflex::Component("bar"));
  a.set("f", true);

  BOOST_CHECK(a.get<int>("a") == 200);
  BOOST_CHECK(a.get<float>("b") == 3.14f);
  BOOST_CHECK(a.get<std::string>("c") == "foo");
  BOOST_CHECK(a.get<corniflex::Component*>("d") != nullptr);
  BOOST_CHECK(a.get<bool>("f") == true);
  BOOST_CHECK(a.get<int>("f") == 0);

  delete a.get<corniflex::Component*>("d");

  a.set("d", nullptr);
  BOOST_CHECK(a.get< corniflex::Component*>("d") == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
