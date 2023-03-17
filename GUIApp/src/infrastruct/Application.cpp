#include "infrastruct/Application.hpp"
#include "infrastruct/Window.hpp"
#include "infrastruct/IApplicationImpl.hpp"
#include <iostream>

Application::StopWrapper::StopWrapper()
{
    _instance = new Application();
}

Application::StopWrapper::~StopWrapper()
{
    if (_instance) {
        delete _instance;
    }
}

Application* Application::StopWrapper::get()
{
    return _instance;
}

void Application::StopWrapper::stop()
{
    delete _instance;
    _instance = nullptr;
}

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
        _window.reset();
        _impl->terminate();
    }
}

Application& Application::getInstance()
{
#ifdef _DEBUG
    return *getStopWrapper().get();
#else
    static Application instance;
    return instance;
#endif //_DEBUG
}

#ifdef _DEBUG
Application::StopWrapper& Application::getStopWrapper()
{
    static Application::StopWrapper wrapper;
    return wrapper;
}
#endif // _DEBUG

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
