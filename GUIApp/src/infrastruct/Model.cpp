#include "infrastruct/Model.hpp"
#include "infrastruct/objects/Batch.hpp"
#include "infrastruct/objects/Light.hpp"


Model::~Model()
{
	for (auto& light : _lights) {
		delete light;
	}

	for (auto& batch : _batches) {
		delete batch;
	}
}

void Model::predraw(DrawStatePoolDef& statePool)
{
	for (auto& light : _lights) {
		light->predraw(statePool);
	}

	auto& currentState = statePool.get();
	_state.apply(currentState);
}

void Model::draw(DrawStatePoolDef& statePool)
{
	for (auto& batch : _batches) {
		statePool.push();
		batch->draw(statePool);
		statePool.pop();
	}
}

Light* Model::createLight()
{
	Light* newLight = new Light();
	_lights.push_back(newLight);
	return newLight;
}

Batch* Model::createBatch()
{
	Batch* newBatch = new Batch();
	_batches.push_back(newBatch);
	return newBatch;
}
