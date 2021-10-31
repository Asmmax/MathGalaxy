#include "BeemanGalaxy.hpp"
#include "GalaxyRegistry.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "components/PreAcceleration.hpp"
#include "components/PrePreAcceleration.hpp"

BeemanGalaxy::BeemanGalaxy() :
	_isFirstStep(true)
{
}

void BeemanGalaxy::step(double deltaTime)
{
	if (_isFirstStep) {
		init(deltaTime);
		_isFirstStep = false;
	}

	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<Position, const Velocity, const Acceleration, const PreAcceleration>().each(
		[deltaTime](auto& pos, auto& vel, auto& acc, auto& preAcc) {
			pos.value += vel.value* deltaTime + (4.0 * acc.value - preAcc.value) * deltaTime * deltaTime / 6.0;
		});

	computeAccelerations();

	registry.view<Velocity, const Acceleration, const PreAcceleration, const PrePreAcceleration>().each(
		[deltaTime](auto& vel, auto& acc, auto& preAcc, auto& prePreAcc) {
			vel.value += (2.0 * acc.value + 5.0 * preAcc.value - prePreAcc.value)* deltaTime / 6.0;
		});
}

void BeemanGalaxy::computeAccelerations()
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<PrePreAcceleration, const PreAcceleration>().each(
		[](auto& prePreAcc, auto& preAcc) {
			prePreAcc.value = preAcc.value;
		});
	registry.view<const PreAcceleration>(entt::exclude<PrePreAcceleration>).each(
		[&registry](auto entity, auto& preAcc) {
			registry.emplace<PrePreAcceleration>(entity, preAcc.value);
		});

	registry.view<PreAcceleration, const Acceleration>().each(
		[](auto& preAcc, auto& acc) {
			preAcc.value = acc.value;
		});

	gravity();
}

void BeemanGalaxy::storePositions()
{
	entt::registry& registry = _registry->getEnttRegistry();

	_tempPositions.resize(registry.size());

	registry.view<const Position>().each(
		[this](auto entity, auto& pos) {
			_tempPositions[static_cast<int>(entity)] = pos.value;
		});
}

void BeemanGalaxy::restorePositions()
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<Position>().each(
		[this](auto entity, auto& pos) {
			pos.value = _tempPositions[static_cast<int>(entity)];
		});
}

void BeemanGalaxy::storeAccelerations()
{
	entt::registry& registry = _registry->getEnttRegistry();

	_tempAccelerations.resize(registry.size());

	registry.view<const Acceleration>().each(
		[this](auto entity, auto& acc) {
			_tempAccelerations[static_cast<int>(entity)] = acc.value;
		});
}

void BeemanGalaxy::restoreAccelerations()
{
	entt::registry& registry = _registry->getEnttRegistry();

	registry.view<Acceleration>().each(
		[this](auto entity, auto& acc) {
			acc.value = _tempAccelerations[static_cast<int>(entity)];
		});
}

void BeemanGalaxy::init(double deltaTime)
{
	entt::registry& registry = _registry->getEnttRegistry();

	storePositions();
	storeAccelerations();

	registry.view<Position, const Velocity, const Acceleration>().each(
		[deltaTime](auto& pos, auto& vel, auto& acc) {
			pos.value -= vel.value * deltaTime - acc.value * deltaTime * deltaTime / 2.0;
		});

	gravity();

	registry.view<const Acceleration>().each(
		[&registry](auto entity, auto& acc) {
			registry.emplace_or_replace<PreAcceleration>(entity, acc.value);
		});

	restoreAccelerations();
	restorePositions();
}
