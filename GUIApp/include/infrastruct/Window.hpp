#pragma once
#include "infrastruct/View.hpp"
#include "infrastruct/Loader.hpp"
#include <memory>
#include <vector>

class IGUI;
class IController;
class IWindowImpl;

class Window
{
	friend class Application;

private:
	IWindowImpl* _impl;
	std::shared_ptr<IGUI> _gui;
	std::shared_ptr<IController> _controller;
	std::vector<View*> _views;
	std::unique_ptr<Loader> _loader;

public:
	~Window();

	void setGUI(const std::shared_ptr<IGUI>& gui);
	void setController(const std::shared_ptr<IController>& controller);

	bool isDone();
	void handle();
	void render();
	View* creteView(int width, int height);
	Loader* getLoader();

private:
	Window(IWindowImpl* impl);

	void setupGUI();

	void mouseButtonCallback(double x, double y);
	void mousePositionCallback(double x, double y);
	void mouseScrollCallback(double yOffset);
};