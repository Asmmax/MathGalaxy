#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"
#include "Transform.hpp"

Camera::Camera(const std::shared_ptr<Transform>& target):
	_target(target)
{
}

void Camera::setupView(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(glm::perspective(45.0f, width / (float)height, 1.0f, 100.0f)));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::inverse(_target->getGlobalMatrix())));
}
