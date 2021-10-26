#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"

#include "schemes/EulerScheme.hpp"
#include "schemes/EulerKromerScheme.hpp"
#include "schemes/CentralDifferenceScheme.hpp"
#include "schemes/VerletScheme.hpp"

#include "helpers/StubView.hpp"

#include <iostream>
#include <string>

#define REQUIRE_MESSAGE(cond, msg) if (!(cond)) { INFO(msg); REQUIRE(cond); }

TEST_CASE("All bodies must move", "[Movement]") 
{
	int stepCount = 1000;
	double step = 0.01;
	double time = step * stepCount;

	std::vector<std::string> schemeNames;
	std::vector<std::shared_ptr<IDifferenceScheme>> schemes;
	std::vector<double> tolerances;

	schemeNames.emplace_back("EulerScheme");
	schemes.emplace_back(std::make_shared<EulerScheme>());
	tolerances.emplace_back(2 * time * step);

	schemeNames.emplace_back("EulerKromerScheme");
	schemes.emplace_back(std::make_shared<EulerKromerScheme>());
	tolerances.emplace_back(2 * time * step);

	schemeNames.emplace_back("CentralDifferenceScheme");
	schemes.emplace_back(std::make_shared<CentralDifferenceScheme>());
	tolerances.emplace_back(2 * time * step * step);

	schemeNames.emplace_back("VerletScheme");
	schemes.emplace_back(std::make_shared<VerletScheme>());
	tolerances.emplace_back(6 * time * step * step * step);

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

		galaxy.start(step);

		for (int i = 1; i < stepCount; i++) {
			galaxy.movement(step);
		}

		galaxy.update(&stubView);

		Vector newPos = startPos + startVel * time + acc / 2 * time * time;
		auto& bodyPos = stubView.getPosition(someBody);

		REQUIRE_MESSAGE(Approx(bodyPos.value.x).margin(tolerances[i]) == newPos.x, schemeNames[i]);
		REQUIRE_MESSAGE(Approx(bodyPos.value.y).margin(tolerances[i]) == newPos.y, schemeNames[i]);
		REQUIRE_MESSAGE(Approx(bodyPos.value.z).margin(tolerances[i]) == newPos.z, schemeNames[i]);
	}
}
