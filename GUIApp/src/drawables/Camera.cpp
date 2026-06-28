#include "drawables/Camera.hpp"

#include "CameraController.hpp"
#include "InputEvents.hpp"
#include "RenderQueue.hpp"
#include "Window.hpp"
#include "drawables/Transform.hpp"
#include "glm/gtx/transform.hpp"


Camera::Camera()
{
	_cameraTarget = std::make_shared<Transform>();
	_cameraEye = std::make_shared<Transform>();
	_cameraTarget->addChild(_cameraEye);
}

void Camera::initController(Window* window)
{
	_controller = std::make_shared<CameraController>(_cameraTarget, _cameraEye);
	window->setMouseButtonCallback([window, controller = _controller](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (key == InputEvents::MouseKey::RIGHT_BUTTON) {
			if (state == InputEvents::KeyState::KEY_DOWN) {
				window->captureMouse();
				controller->startMoving();
			}
			else if (state == InputEvents::KeyState::KEY_UP) {
				window->uncaptureMouse();
				controller->stopMoving();
			}
		}
		});
	window->setMouseMoveCallback([controller = _controller](double posX, double posY) {
		controller->moveMouse(posX, posY);
		});
	window->setMouseScrollCallback([controller = _controller](double step) {
		controller->scrollMouse(step);
		});
}

void Camera::setSkyShader(Shader* skyShader) {_skyShader = skyShader;}
void Camera::setSkyMaterial(Material* skyMaterial) {_skyMaterial = skyMaterial;}
void Camera::setSkyMesh(Mesh* skyMesh) {_skyMesh = skyMesh;}

void Camera::draw(RenderQueue& renderQueue)
{
	RenderCommand skyCmd;
	skyCmd.shader = _skyShader;
	skyCmd.material = _skyMaterial;
	skyCmd.mesh = _skyMesh;
	skyCmd.modelMatrix = _cameraEye->getGlobalMatrix() * glm::scale(glm::vec3(500.0f));
	_skyMaterial->getMaterialData().setVec4(StringId("Origin"), _cameraEye->getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	renderQueue.submit(skyCmd);
}
