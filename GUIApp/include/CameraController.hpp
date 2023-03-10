#pragma once
#include "infrastruct/IController.hpp"
#include <memory>

class Transform;

class CameraController : public IController
{
private:
	std::shared_ptr<Transform> _target;
	std::shared_ptr<Transform> _eye;
	double _lastX;
	double _lastY;
	double _scrollSpeed;
public:
	CameraController(const std::shared_ptr<Transform>& target, const std::shared_ptr<Transform>& eye, double scrollSpeed = 1.2);
	void resetMousePos(double posX, double posY) override;
	void moveMouse(double posX, double posY) override;
	void scrollMouse(double scrollStep) override;
};
