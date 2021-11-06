#include "CameraController.hpp"
#include "Transform.hpp"

CameraController::CameraController(const std::shared_ptr<Transform>& target, const std::shared_ptr<Transform>& eye):
	_target(target),
	_eye(eye),
	_lastX(0),
	_lastY(0)
{
}

void CameraController::resetMousePos(double posX, double posY)
{
	_lastX = posX;
	_lastY = posY;
}

void CameraController::moveMouse(double posX, double posY)
{
	double deltaX = posX - _lastX;
	double deltaY = posY - _lastY;

	auto rotatation = _target->getLocalRotation();

	rotatation.x += static_cast<float>(deltaY);
	rotatation.y += static_cast<float>(deltaX);

	_target->setRotation(rotatation);

	resetMousePos(posX, posY);
}

void CameraController::scrollMouse(int scrollStep)
{

}
