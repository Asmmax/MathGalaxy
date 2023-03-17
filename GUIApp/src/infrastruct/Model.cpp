#include "infrastruct/Model.hpp"

Model::~Model()
{
	for (auto& light : _lights) {
		delete light;
	}

	for (auto& object : _objects) {
		delete object;
	}
}

void Model::predraw(DrawStatePool& statePool)
{
	for (auto& light : _lights) {
		light->predraw(statePool);
	}

	auto& currentState = statePool.get();
	_state.apply(currentState);
}

void Model::draw(DrawStatePool& statePool)
{
	auto& currentState = statePool.get();

	auto& viewMatrix = currentState.getMat4x4("ViewMatrix");
	auto& projMatrix = currentState.getMat4x4("ProjectionMatrix");

	for (auto& object : _objects) 
	{
		statePool.push();
		auto& nextState = statePool.get();

		auto&& modelMatrix = object->getMatrix();

		nextState.add("ModelMatrix", modelMatrix);

		auto modelViewMatrix = viewMatrix * modelMatrix;
		auto normalMatrix4x4 = glm::transpose(glm::inverse(modelViewMatrix));
		glm::mat3 normalMatrix(normalMatrix4x4);

		nextState.add("ModelViewMatrix", modelViewMatrix);
		nextState.add("MVP", projMatrix * modelViewMatrix);
		nextState.add("NormalMatrix", normalMatrix);

		object->draw(statePool);

		statePool.pop();
	}
}

Light* Model::createLight()
{
	Light* newLight = new Light();
	_lights.push_back(newLight);
	return newLight;
}

Object* Model::createObject()
{
	Object* newObject = new Object();
	_objects.push_back(newObject);
	return newObject;
}
