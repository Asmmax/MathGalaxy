#include "Application.hpp"

#include "GLFW/glfw3.h"

Application::Application():
    _isValid(true)
{
    _isValid = glfwInit();
}

Application::~Application()
{
    if (_isValid) {
        glfwTerminate();
    }
}

Application& Application::getInstance()
{
    static Application instance;
    return instance;
}

Window* Application::getWindow(int width, int height, const std::string& title)
{
    if (!_isValid)
        return nullptr;

    if (_window)
    {
        _window.reset();
    }

    _window.reset(new Window(width, height, title));
    return _window.get();
}
