#pragma once
#include "IGraphicsContext.hpp"

struct GLFWwindow;

class GLFWGraphicsContext : public IGraphicsContext
{
private:
	GLFWwindow* _window;

public:
	GLFWGraphicsContext(GLFWwindow* window);

	void init() override;
	void terminate() override;
	void makeCurrent() override;
	ISize getFramebufferSize() override;
	void swapBuffers() override;
	void setupImgui() override;
	void renderImgui() override;
};