#include "widgets/TransformWidget.hpp"
#include "Transform.hpp"
#include "imgui.h"
#include <cmath>

const float pi = 3.1415926536f;

TransformWidget::TransformWidget(const std::string& name, const std::shared_ptr<Transform>& transform):
	_name(name),
	_transform(transform)
{
	auto& pos = transform->getLocalPosition();
	auto& rot = transform->getLocalRotation();
	auto& sc = transform->getLocalScale();

	_position[0] = pos.x;
	_position[1] = pos.y;
	_position[2] = pos.z;

	_rotation[0] = rot.x / pi * 180;
	_rotation[1] = rot.y / pi * 180;
	_rotation[2] = rot.z / pi * 180;

	_scale[0] = sc.x;
	_scale[1] = sc.y;
	_scale[2] = sc.z;
}

void TransformWidget::setup()
{
	std::string windowName = std::string("Transform of ") + _name;
	ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::DragFloat3("Position", _position, 0.1f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat3("Rotation", _rotation, 0.5f, -FLT_MAX, FLT_MAX);
	ImGui::DragFloat3("Scale", _scale, 0.1f, -FLT_MAX, FLT_MAX);
	ImGui::End();

	_rotation[0] = fmod(_rotation[0] + 360.0f, 360.0f);
	_rotation[1] = fmod(_rotation[1] + 360.0f, 360.0f);
	_rotation[2] = fmod(_rotation[2] + 360.0f, 360.0f);

	_transform->setPosition(glm::vec3(_position[0], _position[1], _position[2]));
	_transform->setRotation(glm::vec3(_rotation[0] / 180 * pi, _rotation[1] / 180 * pi, _rotation[2] / 180 * pi));
	_transform->setScale(glm::vec3(_scale[0], _scale[1], _scale[2]));
}
