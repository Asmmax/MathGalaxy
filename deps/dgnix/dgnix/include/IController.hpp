#pragma once

class IController
{
public:
	virtual ~IController() {}
	virtual void resetMousePos(double posX, double posY) = 0;
	virtual void moveMouse(double deltaX, double deltaY) = 0;
	virtual void scrollMouse(double scrollStep) = 0;
};