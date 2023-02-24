#include "impl/GLFWWindowImpl.hpp"
#include "impl/GLFWGraphicsContext.hpp"
#include "impl/GLFWInputHandler.hpp"
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

void GLFWWindowImpl::run(const MainLoopCallback& callback)
{
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		callback();
	}
}

IGraphicsContext* GLFWWindowImpl::getGraphicsContext()
{
	return _graphicsContext.get();
}

IInputHandler* GLFWWindowImpl::getInputHandler()
{
	return _inputHandler.get();
}
