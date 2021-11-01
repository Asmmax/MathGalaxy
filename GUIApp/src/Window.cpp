#include "Window.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Window::Window(int width, int height, const std::string& title):
	_window(nullptr),
	_background{ 0.5f,0.5f,0.5f,1.0f }
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

        int display_w, display_h;
        glfwGetFramebufferSize(_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

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

	//setup GUI
	ImGui::ShowDemoWindow();

	ImGui::Render();
}

void Window::renderGUI()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::renderGeometry()
{

}