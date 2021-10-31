#include "CentralDifferenceGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/PreVelocity.hpp"

void CentralDifferenceGalaxy::step(double deltaTime)
{
	initHalfStep(deltaTime);

	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<Position, PreVelocity, const Acceleration>().each(
		[deltaTime](Position& pos, PreVelocity& vel, const Acceleration& acc) {
		vel.value += acc.value * deltaTime;
		pos.value += vel.value * deltaTime;
		});

	gravity();

	registry.view<Velocity, const PreVelocity, const Acceleration>().each(
		[deltaTime](auto& vel, auto& preVel, auto& acc) {
			vel.value = preVel.value + acc.value * deltaTime / 2;
	});
}

void CentralDifferenceGalaxy::initHalfStep(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<const Velocity, const Acceleration>(entt::exclude<PreVelocity>).each(
		[&registry, deltaTime](auto entity, auto& vel, auto& acc) {
			registry.emplace<PreVelocity>(entity, vel.value - acc.value * deltaTime / 2);
		});
}
