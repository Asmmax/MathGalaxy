#include "infrastruct/impl/GLFWWindowImpl.hpp"
#include "infrastruct/impl/GLFWGraphicsContext.hpp"
#include "infrastruct/impl/GLFWInputHandler.hpp"
#include "gl/gl_core_4_3.hpp"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"

GLFWWindowImpl::GLFWWindowImpl(GLFWwindow* window):
	_window(window),
	_graphicsContext(std::make_unique<GLFWGraphicsContext>(_window)),
	_inputHandler(std::make_unique<GLFWInputHandler>(_window))
{
}

void GLFWWindowImpl::init()
{
	_inputHandler->init();
	_graphicsContext->init();

	ImGui_ImplGlfw_SetCallbacksChainForAllWindows(true);
}

void GLFWWindowImpl::terminate()
{
	_graphicsContext->terminate();
	glfwDestroyWindow(_window);
}

bool GLFWWindowImpl::isDone()
{
	return glfwWindowShouldClose(_window) != 0;
}

void GLFWWindowImpl::handle()
{
	glfwPollEvents();
}

std::weak_ptr<IGraphicsContext> GLFWWindowImpl::getGraphicsContext()
{
	return _graphicsContext;
}

std::weak_ptr<IInputHandler> GLFWWindowImpl::getInputHandler()
{
	return _inputHandler;
}
