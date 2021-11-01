#include "Application.hpp"

int main(int argc, char* argv[])
{
	Application& app = Application::getInstance();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	return window->run();
}