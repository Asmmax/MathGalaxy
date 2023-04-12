#pragma once
#include "View.hpp"
#include "Loader.hpp"
#include <memory>
#include <vector>
#include <functional>

class IGUI;
class IWindowImpl;

class Window
{
	friend class Application;

private:
	using MousePosCallback = std::function<void(double, double)>;
	using MouseScrollCallback = std::function<void(double)>;

	IWindowImpl* _impl;
	std::shared_ptr<IGUI> _gui;
	std::vector<View*> _views;
	std::unique_ptr<Loader> _loader;

	MousePosCallback _resetMousePosCallback;
	MousePosCallback _moveMouseCallback;
	MouseScrollCallback _scrollMouseCallback;

public:
	~Window();

	void setGUI(const std::shared_ptr<IGUI>& gui);

	bool isDone();
	void handle();
	void render();
	View* creteView(int width, int height);
	Loader* getLoader();

	void setResetMousePosCallback(const MousePosCallback& callback) { _resetMousePosCallback = callback; }
	void setMoveMouseCallback(const MousePosCallback& callback) { _moveMouseCallback = callback; }
	void setScrollMouseCallback(const MouseScrollCallback& callback) { _scrollMouseCallback = callback; }

private:
	Window(IWindowImpl* impl);

	void mouseButtonCallback(double x, double y);
	void mousePositionCallback(double x, double y);
	void mouseScrollCallback(double yOffset);
};