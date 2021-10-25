#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

#include "helpers/StubView.hpp"

TEST_CASE("All bodies must move", "[Movement]") 
{
	Galaxy galaxy;
	auto* registry = galaxy.getRegistry();
	StubView stubView;

	Vector startPos{ 5,-4,3 };
	Vector startVel{ 1,2,-3 };
	Vector acc{ 2,1,1 };

	int someBody = registry->createEntity();
	registry->attach(someBody, Position{ startPos });
	registry->attach(someBody, Velocity{ startVel });
	registry->attach(someBody, Acceleration{ acc });

	int stepCount = 1000;
	double step = 0.01;
	double time = step * stepCount;

	for (int i = 0; i < stepCount; i++) {
		galaxy.movement(step);
	}

	galaxy.update(&stubView);

	double tolerance = 2 * time * step;
	Vector newPos = startPos + startVel * time + acc / 2 * time * time;
	auto& bodyPos = stubView.getPosition(someBody);

	REQUIRE(Approx(bodyPos.value.x).margin(tolerance) == newPos.x);
	REQUIRE(Approx(bodyPos.value.y).margin(tolerance) == newPos.y);
	REQUIRE(Approx(bodyPos.value.z).margin(tolerance) == newPos.z);
}
