#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

TEST_CASE("All bodies must move", "[Movement]") 
{
	Galaxy galaxy;
	IGalaxyRegistry* registry = galaxy.getRegistry();

	Vector startPos{ 5,-4,3 };
	Vector startVel{ 1,2,-3 };
	Vector acc{ 2,1,1 };

	int someBody = registry->createEntity();
	auto& bodyPos = registry->attach(someBody, Position{ startPos });
	registry->attach(someBody, Velocity{ startVel });
	registry->attach(someBody, Acceleration{ acc });

	int stepCount = 1000;
	double step = 0.01;
	double time = step * stepCount;

	for (int i = 0; i < stepCount; i++) {
		galaxy.movement(step);
	}

	double tolerance = 2 * time * step;
	Vector newPos = startPos + startVel * time + acc / 2 * time * time;

	REQUIRE(Approx(bodyPos.value.x).margin(tolerance) == newPos.x);
	REQUIRE(Approx(bodyPos.value.y).margin(tolerance) == newPos.y);
	REQUIRE(Approx(bodyPos.value.z).margin(tolerance) == newPos.z);
}
