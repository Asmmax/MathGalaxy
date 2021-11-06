#include "widgets/TransformWidget.hpp"
#include "Transform.hpp"
#include "imgui.h"

TransformWidget::TransformWidget(const std::string& name, const std::shared_ptr<Transform>& transform):
	_name(name),
	_transform(transform)
{
	updateData();
}

void TransformWidget::setup()
{
	updateData();

	std::string windowName = std::string("Transform of ") + _name;
	ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::DragFloat3("Position", _position, 0.1f, -FLT_MAX, FLT_MAX))
	{
		_transform->setPosition(glm::vec3(_position[0], _position[1], _position[2]));
	}

	if (ImGui::DragFloat3("Rotation", _rotation, 0.5f, -FLT_MAX, FLT_MAX))
	{
		_transform->setRotation(glm::vec3(_rotation[0], _rotation[1], _rotation[2]));
	}

	if (ImGui::DragFloat3("Scale", _scale, 0.1f, -FLT_MAX, FLT_MAX))
	{
		_transform->setScale(glm::vec3(_scale[0], _scale[1], _scale[2]));
	}

	ImGui::End();
}

void TransformWidget::updateData()
{
	auto& pos = _transform->getLocalPosition();
	auto& rot = _transform->getLocalRotation();
	auto& sc = _transform->getLocalScale();

	_position[0] = pos.x;
	_position[1] = pos.y;
	_position[2] = pos.z;

	_rotation[0] = rot.x;
	_rotation[1] = rot.y;
	_rotation[2] = rot.z;

	_scale[0] = sc.x;
	_scale[1] = sc.y;
	_scale[2] = sc.z;
}
