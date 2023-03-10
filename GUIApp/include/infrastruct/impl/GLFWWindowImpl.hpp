#pragma once
#include "infrastruct/IWindowImpl.hpp"
#include <memory>
#include <vector>

struct GLFWwindow;

class GLFWWindowImpl : public IWindowImpl
{
private:
	GLFWwindow* _window;
	std::shared_ptr<IGraphicsContext> _graphicsContext;
	std::shared_ptr<IInputHandler> _inputHandler;

public:
	GLFWWindowImpl(GLFWwindow* window);

	void init() override;
	void terminate() override;
	bool isDone() override;
	void handle() override;
	std::weak_ptr<IGraphicsContext> getGraphicsContext() override;
	std::weak_ptr<IInputHandler> getInputHandler() override;
};