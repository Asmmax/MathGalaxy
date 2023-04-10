#pragma once
#include "IGraphicsContext.hpp"
#include "impl/GLLoaderImpl.hpp"
#include <vector>

struct GLFWwindow;
struct ImGuiContext;

class GLFWGraphicsContext : public IGraphicsContext
{
private:
	GLFWwindow* _window;
	ImGuiContext* _imguiContext;

public:
	GLFWGraphicsContext(GLFWwindow* window);

	void init() override;
	void terminate() override;
	void makeCurrent() override;
	ISize getFramebufferSize() override;
	void swapBuffers() override;
	void setupImgui() override;
	void renderImgui() override;

	ILoaderImpl* createLoader() override;
};