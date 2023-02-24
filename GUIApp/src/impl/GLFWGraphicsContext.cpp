#include "impl/GLFWGraphicsContext.hpp"
#include "gl/gl_core_4_3.hpp"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

GLFWGraphicsContext::GLFWGraphicsContext(GLFWwindow* window):
	_window(window)
{
}

void GLFWGraphicsContext::init()
{
	makeCurrent();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init();

	gl::Enable(gl::DEPTH_TEST);
}

void GLFWGraphicsContext::terminate()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GLFWGraphicsContext::makeCurrent()
{
	glfwMakeContextCurrent(_window);
}

GLFWGraphicsContext::ISize GLFWGraphicsContext::getFramebufferSize()
{
	ISize size;
	glfwGetFramebufferSize(_window, &size.width, &size.height);
	return size;
}

void GLFWGraphicsContext::swapBuffers()
{
	glfwSwapBuffers(_window);
}

void GLFWGraphicsContext::setupImgui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
}

void GLFWGraphicsContext::renderImgui()
{
	auto size = getFramebufferSize();
	gl::Viewport(0, 0, size.width, size.height);

	gl::ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	swapBuffers();
}
