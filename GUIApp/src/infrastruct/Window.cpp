#include "infrastruct/Window.hpp"
#include "infrastruct/IGUI.hpp"
#include "infrastruct/IController.hpp"
#include "infrastruct/IWindowImpl.hpp"
#include "infrastruct/IInputHandler.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "infrastruct/IViewImpl.hpp"
#include "infrastruct/Loader.hpp"
#include "imgui.h"

Window::Window(IWindowImpl* impl):
	_impl(impl)
{
	_impl->init();

	if (auto inputHandler = _impl->getInputHandler()) {
		inputHandler->setMouseRightButtonDownCallback([this](double x, double y) {
			mouseButtonCallback(x, y);
			});
		inputHandler->setMouseMoveCallback([this](double x, double y) {
			mousePositionCallback(x, y);
			});
		inputHandler->setMouseScrollCallback([this](double yOffset) {
			mouseScrollCallback(yOffset);
			});
	}
}

Window::~Window()
{
	for (auto& viewPtr : _views) {
		delete viewPtr;
	}

	_loader.reset();

	_impl->terminate();

	delete _impl;
}

void Window::setGUI(const std::shared_ptr<IGUI>& gui)
{
	_gui = gui;

	auto graphicsContext = _impl->getGraphicsContext();
	if (!graphicsContext) {
		return;
	}

	graphicsContext->makeCurrent();

	if (_gui) {
		_gui->init();
	}
}

void Window::setController(const std::shared_ptr<IController>& controller)
{ 
	_controller = controller;
}

bool Window::isDone()
{
	return _impl->isDone();
}

void Window::handle()
{
	_impl->handle();
}

void Window::render()
{
	auto graphicsContext = _impl->getGraphicsContext();
	if (!graphicsContext) {
		return;
	}
	graphicsContext->makeCurrent();

	graphicsContext->setupImgui();
	ImGui::NewFrame();

	if (_gui) {
		_gui->setup();
	}

	ImGui::Render();
	graphicsContext->renderImgui();
	graphicsContext->swapBuffers();
}

View* Window::creteView(int width, int height)
{
	auto graphicsContext = _impl->getGraphicsContext();
	if (!graphicsContext) {
		return nullptr;
	}

	IViewImpl* viewImpl = _impl->createView();
	if (!viewImpl) {
		return nullptr;
	}

	View* newView = new View(viewImpl, width, height);
	newView->init(graphicsContext);
	_views.push_back(newView);
	return newView;
}

Loader* Window::getLoader()
{
	if (!_loader) {
		auto graphicsContext = _impl->getGraphicsContext();
		if (!graphicsContext) {
			return nullptr;
		}

		auto loaderImpl = graphicsContext->createLoader();
		if (!loaderImpl) {
			return nullptr;
		}

		_loader = std::make_unique<Loader>(loaderImpl);
		_loader->init(graphicsContext);
	}
	return _loader.get();
}

void Window::mouseButtonCallback(double posX, double posY)
{
	if (!_controller) {
		return;
	}

	_controller->resetMousePos(posX, posY);
}

void Window::mousePositionCallback(double x, double y)
{
	if (!_controller) {
		return;
	}

	auto inputHandler = _impl->getInputHandler();
	if (!inputHandler) {
		return;
	}

	if (inputHandler->isRightMousePressed()) {
		_controller->moveMouse(x, y);
	}
}

void Window::mouseScrollCallback(double yOffset)
{
	if (!_controller) {
		return;
	}

	_controller->scrollMouse(yOffset);
}
