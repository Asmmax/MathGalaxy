#pragma once
#include "IWidget.hpp"
#include "glm/glm.hpp"
#include <memory>
#include <string>

class Transform;

class TransformWidget : public IWidget
{
private:
	std::string _name;
	std::shared_ptr<Transform> _transform;
	float _position[3];
	float _rotation[3];
	float _scale[3];
public:
	TransformWidget(const std::string& name, const std::shared_ptr<Transform>& transform);
	void setup() override;
};