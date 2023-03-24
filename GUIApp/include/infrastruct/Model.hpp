#pragma once
#include "infrastruct/objects/Object.hpp"
#include "infrastruct/objects/Light.hpp"
#include "infrastruct/DrawState.hpp"
#include <vector>
#include <glm/mat4x4.hpp>

class Model
{
private:
	std::vector<Light*> _lights;
	std::vector<Object*> _objects;
	DrawStateDef _state;
public:
	~Model();

	void predraw(DrawStatePoolDef& statePool);
	void draw(DrawStatePoolDef& statePool);

	DrawStateDef& getState() { return _state; }
	const DrawStateDef& getState() const { return _state; }
	
	Light* createLight();
	Object* createObject();
};
