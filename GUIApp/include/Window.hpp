#pragma once
#include <string>

struct GLFWwindow;

class Window
{
public:
	struct Color {
		float r;
		float g;
		float b;
		float a;
	};

private:
	GLFWwindow* _window;
	Color _background;
public:
	Window(int width, int height, const std::string& title);
	~Window();

	inline void setBackground(const Color& color) { _background = color; }
	inline const Color& getBackground() const { return _background; }

	int run();
private:
	void setupGUI();
	void renderGUI();
	void renderGeometry();
};