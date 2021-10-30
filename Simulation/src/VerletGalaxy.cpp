#include "VerletGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/PreAcceleration.hpp"

void VerletGalaxy::step(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<Position, const Velocity, const Acceleration>().each(
		[deltaTime](auto& pos, auto& vel, auto& acc) {
		pos.value += vel.value * deltaTime + acc.value * deltaTime * deltaTime / 2;
		});

	storeAccelerations();
	gravity();

	registry.view<Velocity, const Acceleration, const PreAcceleration>().each(
		[deltaTime](auto& vel, auto& acc, auto& preAcc) {
		vel.value += (acc.value + preAcc.value) * deltaTime / 2;
		});
}

void VerletGalaxy::storeAccelerations()
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<PreAcceleration, const Acceleration>().each(
		[](auto& preAcc, auto& acc) {
		preAcc.value = acc.value;
		});

	registry.view<const Acceleration>(entt::exclude<PreAcceleration>).each(
		[&registry](auto entity, auto& acc) {
		registry.emplace<PreAcceleration>(entity, acc.value);
		});
}
