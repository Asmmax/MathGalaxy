#include "Galaxy.hpp"
#include "GalaxyRegistry.hpp"

#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/Mass.hpp"

#include <cmath>

const double gravConst = 6.6743e-11;

Galaxy::Galaxy():
	_registry(new GalaxyRegistry())
{
}

IGalaxyRegistry* Galaxy::getRegistry()
{
	return _registry.get();
}

void Galaxy::movement(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Position, Velocity, const Acceleration>();

	celestialBodies.each([deltaTime](Position& pos, Velocity& vel, const Acceleration& acc) {
		pos.value += vel.value * deltaTime;
		vel.value += acc.value * deltaTime;
		});
}

void Galaxy::gravity()
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Acceleration, const Position, const Mass>();

	for (auto firstBody : celestialBodies) {
		auto& firstAcc = celestialBodies.get<Acceleration>(firstBody);
		auto& firstPos = celestialBodies.get<const Position>(firstBody);

		for (auto secondBody : celestialBodies) {

			if (firstBody == secondBody)
				continue;

			auto& secondPos = celestialBodies.get<const Position>(secondBody);
			auto& secondMass = celestialBodies.get<const Mass>(secondBody);

			Vector dir = secondPos.value - firstPos.value;
			firstAcc.value = gravConst * secondMass.value * dir / (dir.length() * dir.sqrLength());
		}
	}
}