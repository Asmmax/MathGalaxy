#pragma once
#include "IWindowImpl.hpp"
#include <memory>
#include <vector>

struct GLFWwindow;

class GLFWWindowImpl : public IWindowImpl
{
private:
	GLFWwindow* _window;
	std::unique_ptr<IGraphicsContext> _graphicsContext;
	std::unique_ptr<IInputHandler> _inputHandler;

public:
	GLFWWindowImpl(GLFWwindow* window);

	void init() override;
	void terminate() override;
	void run(const MainLoopCallback& callback) override;
	IGraphicsContext* getGraphicsContext() override;
	IInputHandler* getInputHandler() override;
};