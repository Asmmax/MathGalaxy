#pragma once
#include <string>
#include <memory>

struct GLFWwindow;
class IWidget;
class IDrawable;

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
	std::shared_ptr<IWidget> _widgetRoot;
	std::shared_ptr<IDrawable> _drawableRoot;
public:
	Window(int width, int height, const std::string& title);
	~Window();

	inline void setWidgetRoot(const std::shared_ptr<IWidget>& widgetRoot) { _widgetRoot = widgetRoot; }
	inline void setDrawableRoot(const std::shared_ptr<IDrawable>& drawableRoot) { _drawableRoot = drawableRoot; }

	inline void setBackground(const Color& color) { _background = color; }
	inline const Color& getBackground() const { return _background; }

	int run();
private:
	void setupGUI();
	void renderGUI();
	void renderGeometry();
};