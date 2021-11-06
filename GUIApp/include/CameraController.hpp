#pragma once
#include "IController.hpp"
#include <memory>

class Transform;

class CameraController : public IController
{
private:
	std::shared_ptr<Transform> _target;
	std::shared_ptr<Transform> _eye;
	double _lastX;
	double _lastY;
public:
	CameraController(const std::shared_ptr<Transform>& target, const std::shared_ptr<Transform>& eye);
	void resetMousePos(double posX, double posY) override;
	void moveMouse(double posX, double posY) override;
	void scrollMouse(int scrollStep) override;
};
