#pragma once
#include "glm/glm.hpp"
#include <memory>

class Transform;

class Camera
{
private:
	std::shared_ptr<Transform> _target;
public:
	Camera(const std::shared_ptr<Transform>& target);

	inline void setTarget(const std::shared_ptr<Transform>& target) { _target = target; }
	void setupView(int width, int height);
};