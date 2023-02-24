#include "Window.hpp"
#include "gui/GUI.hpp"
#include "IDrawable.hpp"
#include "Transform.hpp"
#include "IController.hpp"
#include "IWindowImpl.hpp"
#include "IInputHandler.hpp"
#include "IGraphicsContext.hpp"
#include "View.hpp"
#include "imgui.h"

Window::Window(IWindowImpl* impl):
	_impl(impl)
{
	auto inputHandler = _impl->getInputHandler();
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

void Window::setGUI(const std::shared_ptr<IGUI>& gui)
{
	_gui = gui;

	if (_gui) {
		_gui->init();
	}
}

void Window::setDrawableRoot(const std::shared_ptr<IDrawable>& drawableRoot)
{ 
	_drawableRoot = drawableRoot;

	if (_drawableRoot) {
		_drawableRoot->init();
	}
}

void Window::setController(const std::shared_ptr<IController>& controller)
{ 
	_controller = controller;
}

int Window::run()
{
	_impl->run([this]() {
		runImpl();
		});
	return 0;
}

std::weak_ptr<View> Window::creteView(int width, int height, const std::shared_ptr<Transform>& target)
{
	auto view = std::make_shared<View>(width, height, target);
	view->init();

	_views.push_back(view);
	return _views.back();
}

void Window::runImpl()
{
	if (_transformRoot) {
		_transformRoot->computeGlobalMatrices();
	}
	for (auto& view : _views) {
		view->render(_drawableRoot.get());
	}

	auto&& graphicsContext = _impl->getGraphicsContext();
	graphicsContext->setupImgui();
	setupGUI();
	graphicsContext->renderImgui();
}

void Window::setupGUI()
{
	ImGui::NewFrame();

	if (_gui)
	{
		_gui->setup();
	}

	ImGui::Render();
}

void Window::mouseButtonCallback(double posX, double posY)
{
	_controller->resetMousePos(posX, posY);
}

void Window::mousePositionCallback(double x, double y)
{
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
	_controller->scrollMouse(yOffset);
}
