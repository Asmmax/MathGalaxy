#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Mass.hpp"
#include "components/Acceleration.hpp"

const double gravConst = 6.6743e-11;

TEST_CASE("All bodies with mass must gravitate", "[Gravity]")
{
	Galaxy galaxy;
	auto* registry = galaxy.getRegistry();

	Position firstPos{ 1,0,0 };
	Mass firstMass{ 5e10 };

	Position secondPos{ 1,1,0 };
	Mass secondMass{ 15e10 };

	int firstBody = registry->createEntity();
	registry->attach(firstBody, firstMass);
	registry->attach(firstBody, firstPos);
	auto& firstBodyAcc = registry->attach(firstBody, Acceleration{ 0,0,0 });

	int secondBody = registry->createEntity();
	auto& secondBodyPos = registry->attach(secondBody, secondPos);
	auto& secondBodyAcc = registry->attach(secondBody, Acceleration{ 0,0,0 });
	registry->attach(secondBody, secondMass);

	galaxy.gravity();

	REQUIRE(Approx(firstBodyAcc.value.y) == gravConst * secondMass.value);
	REQUIRE(Approx(secondBodyAcc.value.y) == -gravConst * firstMass.value);
}
