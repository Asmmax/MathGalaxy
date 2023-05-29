#pragma once
#include <glm/vec3.hpp>
#include <memory>

class Transform;

class CameraController
{
private:
	std::shared_ptr<Transform> _target;
	std::shared_ptr<Transform> _eye;
	glm::vec3 _storagedRotation;
	double _lastX;
	double _lastY;
	double _sumDeltaX;
	double _sumDeltaY;
	double _scrollSpeed;
	bool _isMoving;

public:
	CameraController(const std::shared_ptr<Transform>& target, const std::shared_ptr<Transform>& eye, double scrollSpeed = 1.2);
	void stopMoving();
	void startMoving();
	void moveMouse(double posX, double posY);
	void scrollMouse(double scrollStep);
};
