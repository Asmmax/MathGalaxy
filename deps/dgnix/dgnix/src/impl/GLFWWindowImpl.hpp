#pragma once
#include "IWindowImpl.hpp"
#include "impl/GLFWGraphicsContext.hpp"
#include "impl/GLFWInputHandler.hpp"
#include "impl/GLViewImpl.hpp"
#include <vector>

struct GLFWwindow;

class GLFWWindowImpl : public IWindowImpl
{
private:
	GLFWwindow* _window;
	GLFWGraphicsContext _graphicsContext;
	GLFWInputHandler _inputHandler;

public:
	GLFWWindowImpl(GLFWwindow* window);

	void init() override;
	void terminate() override;
	bool isDone() override;
	void handle() override;
	IGraphicsContext* getGraphicsContext() override;
	IInputHandler* getInputHandler() override;

	IViewImpl* createView() override;
};