#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "EulerGalaxy.hpp"
#include "EulerKromerGalaxy.hpp"
#include "CentralDifferenceGalaxy.hpp"
#include "VerletGalaxy.hpp"
#include "BeemanGalaxy.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Mass.hpp"
#include "components/Acceleration.hpp"

#include "helpers/StubView.hpp"

const double gravConst = 6.6743e-11;
const double pi = 3.1415926535897932;

TEST_CASE("Two-body problem with the same orbit", "[Movement]")
{
	double time = 10*pi;
	int stepCount = 1000;
	double deltaTime = time / stepCount;

	std::vector<std::string> schemeNames;
	std::vector<std::shared_ptr<Galaxy>> galaxies;
	std::vector<double> posTolerances;
	std::vector<double> velTolerances;

	schemeNames.emplace_back("EulerGalaxy");
	galaxies.emplace_back(std::make_shared<EulerGalaxy>());
	posTolerances.emplace_back(10);
	velTolerances.emplace_back(10);

	schemeNames.emplace_back("EulerKromerGalaxy");
	galaxies.emplace_back(std::make_shared<EulerKromerGalaxy>());
	posTolerances.emplace_back(200 * deltaTime * deltaTime);
	velTolerances.emplace_back(200 * deltaTime * deltaTime);

	schemeNames.emplace_back("CentralDifferenceGalaxy");
	galaxies.emplace_back(std::make_shared<CentralDifferenceGalaxy>());
	posTolerances.emplace_back(100 * deltaTime * deltaTime);
	velTolerances.emplace_back(100 * deltaTime * deltaTime);

	schemeNames.emplace_back("VerletGalaxy");
	galaxies.emplace_back(std::make_shared<VerletGalaxy>());
	posTolerances.emplace_back(100 * deltaTime * deltaTime);
	velTolerances.emplace_back(100 * deltaTime * deltaTime);

	schemeNames.emplace_back("BeemanGalaxy");
	galaxies.emplace_back(std::make_shared<BeemanGalaxy>());
	posTolerances.emplace_back(50 * deltaTime * deltaTime);
	velTolerances.emplace_back(50 * deltaTime * deltaTime);

	for (int i = 0; i < galaxies.size(); i++) {

		Galaxy& galaxy = *galaxies[i];
		auto* registry = galaxy.getRegistry();
		StubView stubView;

		int firstBody = registry->createEntity();
		registry->attach(firstBody, Position{ 0,0,0 });
		registry->attach(firstBody, Velocity{ 0,1,0 });
		registry->attach(firstBody, Acceleration{ 0,0,0 });
		registry->attach(firstBody, Mass{ 2 / gravConst });

		int secondBody = registry->createEntity();
		registry->attach(secondBody, Position{ 1,0,0 });
		registry->attach(secondBody, Velocity{ 0,-1,0 });
		registry->attach(secondBody, Acceleration{ 0,0,0 });
		registry->attach(secondBody, Mass{ 2 / gravConst });

		galaxy.gravity();
		for (int i = 0; i < stepCount; i++) {
			galaxy.step(deltaTime);
		}

		galaxy.update(&stubView);

		auto& firstBodyPos = stubView.getPosition(firstBody);
		auto& secondBodyPos = stubView.getPosition(secondBody);

		double fisrtDist = (firstBodyPos.value - Vector{ 0,0,0 }).length();
		double secondDist = (secondBodyPos.value - Vector{ 1,0,0 }).length();

		INFO(schemeNames[i]);
		REQUIRE(Approx(fisrtDist).margin(posTolerances[i]) == 0.);
		REQUIRE(Approx(secondDist).margin(posTolerances[i]) == 0.);

		auto& firstBodyVel = stubView.getVelocity(firstBody);
		auto& secondBodyVel = stubView.getVelocity(secondBody);

		double firstDev = (firstBodyVel.value - Vector{ 0,1,0 }).length();
		double secondDev = (secondBodyVel.value - Vector{ 0,-1,0 }).length();

		REQUIRE(Approx(firstDev).margin(velTolerances[i]) == 0.);
		REQUIRE(Approx(secondDev).margin(velTolerances[i]) == 0.);
	}
}
