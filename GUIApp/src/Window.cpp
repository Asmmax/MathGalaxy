#include "Window.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "gui/GUI.hpp"
#include "IDrawable.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "IController.hpp"

Window::Window(int width, int height, const std::string& title):
	_window(nullptr),
	_background{ 0.5f,0.5f,0.5f,1.0f },
	_width(1),
	_height(1)
{
	_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (_window)
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(_window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init();

		glEnable(GL_DEPTH_TEST);

		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		glfwSetMouseButtonCallback(_window, mouseButtonCallback);
		glfwSetCursorPosCallback(_window, mousePositionCallback);
		glfwSetScrollCallback(_window, mouseScrollCallback);
	}
}

Window::~Window()
{
	if (_window) 
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(_window);
	}
}

void Window::setController(const std::shared_ptr<IController>& controller)
{ 
	_controller = controller;
	glfwSetWindowUserPointer(_window, static_cast<void*>(_controller.get()));
}

int Window::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(_window))
    {
		glfwPollEvents();

		setupGUI();

        glfwGetFramebufferSize(_window, &_width, &_height);
        glViewport(0, 0, _width, _height);

		glClearColor(_background.r*_background.a, _background.g * _background.a, _background.b * _background.a, _background.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderGeometry();
		renderGUI();

        glfwSwapBuffers(_window);

    }
    return 0;
}

void Window::setupGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (_gui)
	{
		_gui->setup();
	}

	ImGui::Render();
}

void Window::renderGUI()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::renderGeometry()
{
	if (_transformRoot)
	{
		_transformRoot->computeGlobalMatrices();
	}
	if (_camera)
	{
		_camera->setupView(_width, _height);
	}
	if (_drawableRoot)
	{
		_drawableRoot->draw();
	}
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mode);

	auto* controller = static_cast<IController*>(glfwGetWindowUserPointer(window));

	if (!controller)
		return;

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			
			double posX = 0, posY = 0;
			glfwGetCursorPos(window, &posX, &posY);
			controller->resetMousePos(posX, posY);
		}
		else if (action == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		}
	}
}

void Window::mousePositionCallback(GLFWwindow* window, double x, double y)
{
	ImGui_ImplGlfw_CursorPosCallback(window, x, y);

	auto* controller = static_cast<IController*>(glfwGetWindowUserPointer(window));

	if (!controller)
		return;

	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS)
	{
		controller->moveMouse(x, y);
	}
}

void Window::mouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
		ImGui_ImplGlfw_ScrollCallback(window, xOffset, yOffset);
		return;
	}

	auto* controller = static_cast<IController*>(glfwGetWindowUserPointer(window));

	if (!controller)
		return;

	controller->scrollMouse(yOffset);
}
