#include "Application.hpp"
#include "widgets/DemoWidget.hpp"
#include "drawables/Triangle.hpp"

int main(int argc, char* argv[])
{
	Application& app = Application::getInstance();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	auto widget = std::make_shared<DemoWidget>();
	window->setWidgetRoot(widget);

	auto drawable = std::make_shared<Triangle>();
	window->setDrawableRoot(drawable);

	return window->run();
}