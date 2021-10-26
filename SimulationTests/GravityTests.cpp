#include "catch.hpp"
#include "IGalaxyRegistry.hpp"
#include "Galaxy.hpp"

#include "components/Position.hpp"
#include "components/Mass.hpp"
#include "components/Acceleration.hpp"

#include "helpers/StubView.hpp"

#include "schemes/EulerScheme.hpp"
#include "schemes/EulerKromerScheme.hpp"
#include "schemes/CentralDifferenceScheme.hpp"
#include "schemes/VerletScheme.hpp"

const double gravConst = 6.6743e-11;
const double pi = 3.1415926535897932;
#define REQUIRE_MESSAGE(cond, msg) if (!(cond)) { INFO(msg); REQUIRE(cond); }

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

TEST_CASE("Bodies can have normal acceleration", "[Movement]")
{
	double time = pi;
	int stepCount = 1000;
	double step = time / stepCount;

	std::vector<std::string> schemeNames;
	std::vector<std::shared_ptr<IDifferenceScheme>> schemes;
	std::vector<double> tolerances;

	schemeNames.emplace_back("EulerScheme");
	schemes.emplace_back(std::make_shared<EulerScheme>());
	tolerances.emplace_back(6 * time * step);

	schemeNames.emplace_back("EulerKromerScheme");
	schemes.emplace_back(std::make_shared<EulerKromerScheme>());
	tolerances.emplace_back(6 * time * step);

	schemeNames.emplace_back("CentralDifferenceScheme");
	schemes.emplace_back(std::make_shared<CentralDifferenceScheme>());
	tolerances.emplace_back(6 * time * step * step);

	schemeNames.emplace_back("VerletScheme");
	schemes.emplace_back(std::make_shared<VerletScheme>());
	tolerances.emplace_back(6 * time * step * step * step);

	for (int i = 0; i < schemes.size(); i++) {

		Galaxy galaxy(schemes[i]);
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
		galaxy.start(step);

		for (int i = 1; i < stepCount; i++) {
			galaxy.gravity();
			galaxy.movement(step);
		}

		galaxy.update(&stubView);

		auto& firstBodyPos = stubView.getPosition(firstBody);
		auto& secondBodyPos = stubView.getPosition(secondBody);

		REQUIRE_MESSAGE(Approx(firstBodyPos.value.x).margin(tolerances[i]) == 0., schemeNames[i]);
		REQUIRE_MESSAGE(Approx(secondBodyPos.value.x).margin(tolerances[i]) == 1., schemeNames[i]);
	}
}
