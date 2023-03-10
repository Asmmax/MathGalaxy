#include "infrastruct/Window.hpp"
#include "infrastruct/IGUI.hpp"
#include "infrastruct/IDrawable.hpp"
#include "infrastruct/IController.hpp"
#include "infrastruct/IWindowImpl.hpp"
#include "infrastruct/IInputHandler.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "infrastruct/View.hpp"
#include "imgui.h"

Window::Window(IWindowImpl* impl):
	_impl(impl)
{
	if (auto inputHandler = _impl->getInputHandler().lock()) {
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

void Window::setGUI(const std::shared_ptr<IGUI>& gui)
{
	_gui = gui;

	auto graphicsContext = _impl->getGraphicsContext();
	if (graphicsContext.expired()) {
		return;
	}

	if (_gui) {
		_gui->init(graphicsContext);
	}
}

void Window::setDrawableRoot(const std::shared_ptr<IDrawable>& drawableRoot)
{ 
	_drawableRoot = drawableRoot;

	auto graphicsContext = _impl->getGraphicsContext();
	if (graphicsContext.expired()) {
		return;
	}

	if (_drawableRoot) {
		_drawableRoot->init(graphicsContext);
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
	if (!_drawableRoot) {
		return;
	}

	auto graphicsContext = _impl->getGraphicsContext().lock();
	if (!graphicsContext) {
		return;
	}
	graphicsContext->makeCurrent();

	for (auto& view : _views) {
		view->render(_drawableRoot.get());
	}
}

void Window::renderGUI()
{
	auto graphicsContext = _impl->getGraphicsContext().lock();
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
}

std::weak_ptr<View> Window::creteView(int width, int height)
{
	auto graphicsContext = _impl->getGraphicsContext();
	if (graphicsContext.expired()) {
		return std::weak_ptr<View>();
	}

	auto view = std::make_shared<View>(width, height);
	view->init(graphicsContext);

	_views.push_back(view);
	return _views.back();
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

	auto inputHandler = _impl->getInputHandler().lock();
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
