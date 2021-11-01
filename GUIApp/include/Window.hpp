#pragma once
#include <string>

struct GLFWwindow;

class Window
{
private:
	GLFWwindow* _window;
public:
	Window(int width, int height, const std::string& title);
	~Window();

	int run();
};