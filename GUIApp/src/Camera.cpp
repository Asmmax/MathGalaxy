#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "Transform.hpp"

Camera::Camera(const std::shared_ptr<Transform>& target):
	_target(target),
	_projectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 100.0f))
{
}

void Camera::setupView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(_projectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::inverse(_target->getGlobalMatrix())));
}
