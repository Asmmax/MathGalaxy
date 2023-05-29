#include "CameraController.hpp"
#include "drawables/Transform.hpp"

CameraController::CameraController(const std::shared_ptr<Transform>& target, const std::shared_ptr<Transform>& eye, double scrollSpeed):
	_target(target),
	_eye(eye),
	_lastX(0),
	_lastY(0),
	_sumDeltaX(0),
	_sumDeltaY(0),
	_scrollSpeed(scrollSpeed),
	_isMoving(false)
{
	_storagedRotation = _target->getLocalRotation();
}

void CameraController::stopMoving()
{
	_isMoving = false;
}

void CameraController::startMoving()
{
	_sumDeltaX = 0.0;
	_sumDeltaY = 0.0;
	_storagedRotation = _target->getLocalRotation();
	_isMoving = true;
}

void CameraController::moveMouse(double posX, double posY)
{
	_sumDeltaX += posX - _lastX;
	_sumDeltaY += posY - _lastY;
	_lastX = posX;
	_lastY = posY;

	if (!_isMoving) {
		return;
	}

	auto rotatation = _storagedRotation;

	rotatation.x += static_cast<float>(_sumDeltaY);
	rotatation.y += static_cast<float>(_sumDeltaX);

	_target->setRotation(rotatation);
}

void CameraController::scrollMouse(double scrollStep)
{
	double scale = glm::pow(_scrollSpeed, -scrollStep);

	auto position = _eye->getLocalPosition();
	position.z *= static_cast<float>(scale);
	_eye->setPosition(position);
}
