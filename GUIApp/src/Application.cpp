#include "Application.hpp"
#include "Window.hpp"
#include "IApplicationImpl.hpp"

Application::Application():
    _isValid(false)
{
}

void Application::initGraphics()
{
    if (_impl) {
        _isValid = _impl->init();
    }
}

Application::~Application()
{
    if (_isValid && _impl) {
        _impl->terminate();
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

    if (!_impl)
        return nullptr;

    auto windowImpl = _impl->createWindow(width, height, title);
    if (!windowImpl) {
        return nullptr;
    }

    _window.reset(new Window(windowImpl));
    return _window.get();
}
