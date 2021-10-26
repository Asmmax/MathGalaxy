#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

#include "schemes/EulerScheme.hpp"
#include "schemes/EulerKromerScheme.hpp"

#include "helpers/StubView.hpp"

#include <iostream>
#include <string>

#define REQUIRE_MESSAGE(cond, msg) if (!(cond)) { INFO(msg); REQUIRE(cond); }

TEST_CASE("All bodies must move", "[Movement]") 
{
	std::vector<std::string> schemeNames;
	std::vector<std::shared_ptr<IDifferenceScheme>> schemes;

	schemeNames.emplace_back("EulerScheme");
	schemes.emplace_back(std::make_shared<EulerScheme>());

	schemeNames.emplace_back("EulerKromerScheme");
	schemes.emplace_back(std::make_shared<EulerKromerScheme>());

	for (int i = 0; i < schemes.size(); i++) {

		Galaxy galaxy(schemes[i]);
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

		REQUIRE_MESSAGE(Approx(bodyPos.value.x).margin(tolerance) == newPos.x, schemeNames[i]);
		REQUIRE_MESSAGE(Approx(bodyPos.value.y).margin(tolerance) == newPos.y, schemeNames[i]);
		REQUIRE_MESSAGE(Approx(bodyPos.value.z).margin(tolerance) == newPos.z, schemeNames[i]);
	}
}
