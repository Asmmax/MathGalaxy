#pragma once
#include "infrastruct/DrawState.hpp"
#include <vector>
#include <glm/mat4x4.hpp>

class Light;
class Object;
class Batch;

class Model
{
private:
	std::vector<Light*> _lights;
	std::vector<Batch*> _batches;
	DrawStateDef _state;
public:
	~Model();

	void predraw(DrawStatePoolDef& statePool);
	void draw(DrawStatePoolDef& statePool);

	DrawStateDef& getState() { return _state; }
	const DrawStateDef& getState() const { return _state; }
	
	Light* createLight();
	Batch* createBatch();
};
