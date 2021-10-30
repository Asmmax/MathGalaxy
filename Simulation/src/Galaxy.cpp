#include "Galaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "IView.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/Mass.hpp"

const double gravConst = 6.6743e-11;

Galaxy::Galaxy():
	_registry(new GalaxyRegistry())
{
}

Galaxy::~Galaxy()
{
}

IGalaxyRegistry* Galaxy::getRegistry()
{
	return _registry.get();
}

void Galaxy::gravity()
{
	entt::registry& registry = _registry->getEnttRegistry();

	auto celestialBodies = registry.view<Acceleration, const Position, const Mass>();

	for (auto firstBody : celestialBodies) {
		auto& firstAcc = celestialBodies.get<Acceleration>(firstBody);
		auto& firstPos = celestialBodies.get<const Position>(firstBody);

		firstAcc.value.toZero();
		for (auto secondBody : celestialBodies) {

			if (firstBody == secondBody)
				continue;

			auto& secondPos = celestialBodies.get<const Position>(secondBody);
			auto& secondMass = celestialBodies.get<const Mass>(secondBody);

			Vector dir = secondPos.value - firstPos.value;
			firstAcc.value += gravConst * secondMass.value * dir / (dir.length() * dir.sqrLength());
		}
	}
}

void Galaxy::update(IView* view)
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<const Position>().each([view](auto entity, const Position& pos) {
		view->update(static_cast<int>(entity), pos);
		});

	registry.view<const Velocity>().each([view](auto entity, const Velocity& vel) {
		view->update(static_cast<int>(entity), vel);
		});

	registry.view<const Acceleration>().each([view](auto entity, const Acceleration& acc) {
		view->update(static_cast<int>(entity), acc);
		});
}