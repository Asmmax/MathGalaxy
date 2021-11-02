#pragma once
#include <string>
#include <memory>

struct GLFWwindow;
class IWidget;
class IDrawable;
class Transform;
class Camera;

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
	std::shared_ptr<Transform> _transformRoot;
	std::shared_ptr<Camera> _camera;
public:
	Window(int width, int height, const std::string& title);
	~Window();

	inline void setWidgetRoot(const std::shared_ptr<IWidget>& widgetRoot) { _widgetRoot = widgetRoot; }
	inline void setDrawableRoot(const std::shared_ptr<IDrawable>& drawableRoot) { _drawableRoot = drawableRoot; }
	inline void setTransformRoot(const std::shared_ptr<Transform>& transformRoot) { _transformRoot = transformRoot; }
	inline void setCamera(const std::shared_ptr<Camera>& camera) { _camera = camera; }

	inline void setBackground(const Color& color) { _background = color; }
	inline const Color& getBackground() const { return _background; }

	int run();
private:
	void setupGUI();
	void renderGUI();
	void renderGeometry();
};