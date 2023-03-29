#pragma once
#include "infrastruct/DrawState.hpp"
#include <vector>

class Shader;
class Texture;
class Object;

class Batch
{
private:
	DrawStateDef _state;
	Shader* _shader;
	std::vector<std::pair<StringId, Texture*>> _textures;
	std::vector<Object*> _objects;

public:
	Batch();

	DrawStateDef& getState() { return _state; }
	const DrawStateDef& getState() const { return _state; }

	void setShader(Shader* shader);

	bool hasTexture(const StringId& name) const;
	void addTexture(const StringId& name, Texture* texture);
	void setTexture(const StringId& name, Texture* texture);
	void removeTexture(const StringId& name);

	Object* createObject();

	void draw(DrawStatePoolDef& statePool);
};
