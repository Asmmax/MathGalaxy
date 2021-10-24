#include "catch.hpp"
#include "IWorld.hpp"
#include "Simulation.hpp"

#include "components/Position.hpp"
#include "components/Mass.hpp"
#include "components/Acceleration.hpp"

const double gravConst = 6.6743e-11;

TEST_CASE("All bodies with mass must gravitate", "[Gravity]")
{
	Simulation simul;
	IWorld* world = simul.getWorld();

	Position firstPos{ 1,0,0 };
	Mass firstMass{ 5e10 };

	Position secondPos{ 1,1,0 };
	Mass secondMass{ 15e10 };

	int firstBody = world->createEntity();
	world->attach(firstBody, firstMass);
	world->attach(firstBody, firstPos);
	auto& firstBodyAcc = world->attach(firstBody, Acceleration{ 0,0,0 });

	int secondBody = world->createEntity();
	auto& secondBodyPos = world->attach(secondBody, secondPos);
	auto& secondBodyAcc = world->attach(secondBody, Acceleration{ 0,0,0 });
	world->attach(secondBody, secondMass);

	simul.gravity();

	REQUIRE(Approx(firstBodyAcc.value.y) == gravConst * secondMass.value);
	REQUIRE(Approx(secondBodyAcc.value.y) == -gravConst * firstMass.value);
}
