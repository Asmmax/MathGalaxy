#pragma once
#include <memory>
#include <string>

#include "Window.hpp"

class Application
{
private:
	bool _isValid;
	std::unique_ptr<Window> _window;
private:
	Application();

public:
	~Application();
	Application(const Application& other) = delete;
	void operator=(const Application& other) = delete;
	static Application& getInstance();

	Window* getWindow(int width, int height, const std::string& title);
};