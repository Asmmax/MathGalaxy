#include "Application.hpp"

int main(int argc, char* argv[])
{
	Application& app = Application::getInstance();
	return app.run();
}