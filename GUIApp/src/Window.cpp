#include "Window.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "IWidget.hpp"
#include "IDrawable.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

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

	if (_widgetRoot)
	{
		_widgetRoot->setup();
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