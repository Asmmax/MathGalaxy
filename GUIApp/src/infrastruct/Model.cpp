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

	static StringId viewMatrixName = StringId("ViewMatrix");
	auto& viewMatrix = currentState.getMat4x4(viewMatrixName);

	static StringId projMatrixName = StringId("ProjectionMatrix");
	auto& projMatrix = currentState.getMat4x4(projMatrixName);

	for (auto& object : _objects) 
	{
		statePool.push();
		auto& nextState = statePool.get();

		auto&& modelMatrix = object->getMatrix();

		static StringId modelMatrixName = StringId("ModelMatrix");
		nextState.add(modelMatrixName, modelMatrix);

		auto modelViewMatrix = viewMatrix * modelMatrix;
		auto normalMatrix4x4 = glm::transpose(glm::inverse(modelViewMatrix));
		glm::mat3 normalMatrix(normalMatrix4x4);

		static StringId modelViewMatrixName = StringId("ModelViewMatrix");
		nextState.add(modelViewMatrixName, modelViewMatrix);

		static StringId mvpMatrixName = StringId("MVP");
		nextState.add(mvpMatrixName, projMatrix * modelViewMatrix);

		static StringId normalMatrixName = StringId("NormalMatrix");
		nextState.add(normalMatrixName, normalMatrix);

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
