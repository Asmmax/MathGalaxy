#pragma once
#include "glm/glm.hpp"
#include <memory>

class Transform;

class Camera
{
private:
	std::shared_ptr<Transform> _target;
	glm::mat4 _projectionMatrix;
public:
	Camera(const std::shared_ptr<Transform>& target);

	inline void setTarget(const std::shared_ptr<Transform>& target) { _target = target; }
	void setupView();
};