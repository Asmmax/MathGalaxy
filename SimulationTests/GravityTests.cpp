#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Mass.hpp"
#include "components/Acceleration.hpp"

#include "helpers/StubView.hpp"

const double gravConst = 6.6743e-11;

TEST_CASE("All bodies with mass must gravitate", "[Gravity]")
{
	Galaxy galaxy;
	auto* registry = galaxy.getRegistry();
	StubView stubView;

	Position firstPos{ 1,0,0 };
	Mass firstMass{ 5e10 };

	Position secondPos{ 1,1,0 };
	Mass secondMass{ 15e10 };

	int firstBody = registry->createEntity();
	registry->attach(firstBody, firstMass);
	registry->attach(firstBody, firstPos);
	registry->attach(firstBody, Acceleration{ 0,0,0 });

	int secondBody = registry->createEntity();
	registry->attach(secondBody, secondPos);
	registry->attach(secondBody, Acceleration{ 0,0,0 });
	registry->attach(secondBody, secondMass);

	galaxy.gravity();
	galaxy.update(&stubView);

	auto& firstBodyAcc = stubView.getAcceleration(firstBody);
	auto& secondBodyAcc = stubView.getAcceleration(secondBody);

	REQUIRE(Approx(firstBodyAcc.value.y) == gravConst * secondMass.value);
	REQUIRE(Approx(secondBodyAcc.value.y) == -gravConst * firstMass.value);
}


TEST_CASE("All bodies with mass must gravitate to some other bodies", "[Gravity]")
{
	Galaxy galaxy;
	auto* registry = galaxy.getRegistry();
	StubView stubView;

	Position firstPos{ 0,0,0 };
	Mass firstMass{ 5e10 };

	Position secondPos{ 0,-1,0 };
	Mass secondMass{ 15e10 };

	Position thirdPos{ 0,1,0 };
	Mass thirdMass{ 10e10 };

	int firstBody = registry->createEntity();
	registry->attach(firstBody, firstMass);
	registry->attach(firstBody, firstPos);
	registry->attach(firstBody, Acceleration{ 0,0,0 });

	int secondBody = registry->createEntity();
	registry->attach(secondBody, secondPos);
	registry->attach(secondBody, Acceleration{ 0,0,0 });
	registry->attach(secondBody, secondMass);

	int thirdBody = registry->createEntity();
	registry->attach(thirdBody, thirdPos);
	registry->attach(thirdBody, Acceleration{ 0,0,0 });
	registry->attach(thirdBody, thirdMass);

	galaxy.gravity();
	galaxy.update(&stubView);

	auto& firstBodyAcc = stubView.getAcceleration(firstBody);
	auto& secondBodyAcc = stubView.getAcceleration(secondBody);
	auto& thirdBodyAcc = stubView.getAcceleration(thirdBody);

	REQUIRE(Approx(firstBodyAcc.value.y) == -gravConst * secondMass.value + gravConst * thirdMass.value);
	REQUIRE(Approx(secondBodyAcc.value.y) == gravConst * firstMass.value + gravConst * thirdMass.value / 4);
	REQUIRE(Approx(thirdBodyAcc.value.y) == -gravConst * firstMass.value - gravConst * secondMass.value / 4);
}