#include	<boost/test/unit_test.hpp>

#include	"corniflex/Entity.hh"

BOOST_AUTO_TEST_SUITE(EntityTesting)

BOOST_AUTO_TEST_CASE(EntityIDIncrementationTest)
{
  corniflex::Entity	a;
  corniflex::Entity	b;
  corniflex::Entity	c;

  BOOST_CHECK(a.getID() == 1);
  BOOST_CHECK(b.getID() == 2);
  BOOST_CHECK(c.getID() == 3);
}

BOOST_AUTO_TEST_SUITE_END()
