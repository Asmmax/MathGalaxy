#pragma once
#include <string>
#include <memory>
#include <vector>

class IGUI;
class IDrawable;
class Transform;
class IController;
class IWindowImpl;
class View;

class Window
{
	friend class Application;

private:
	IWindowImpl* _impl;
	std::shared_ptr<IGUI> _gui;
	std::shared_ptr<IDrawable> _drawableRoot;
	std::shared_ptr<Transform> _transformRoot;
	std::shared_ptr<IController> _controller;
	std::vector<std::shared_ptr<View>> _views;

public:
	void setGUI(const std::shared_ptr<IGUI>& gui);
	void setDrawableRoot(const std::shared_ptr<IDrawable>& drawableRoot);
	void setTransformRoot(const std::shared_ptr<Transform>& transformRoot) { _transformRoot = transformRoot; }
	void setController(const std::shared_ptr<IController>& controller);

	int run();
	std::weak_ptr<View> creteView(int width, int height, const std::shared_ptr<Transform>& target = nullptr);

private:
	Window(IWindowImpl* impl);

	void setupGUI();
	void runImpl();

	void mouseButtonCallback(double x, double y);
	void mousePositionCallback(double x, double y);
	void mouseScrollCallback(double yOffset);
};