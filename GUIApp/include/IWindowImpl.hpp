#pragma once
#include <functional>

class IGraphicsContext;
class IInputHandler;

class IWindowImpl
{
public:
	using MainLoopCallback = std::function<void()>;

	virtual ~IWindowImpl() {}

	virtual void init() = 0;
	virtual void terminate() = 0;
	virtual void run(const MainLoopCallback& callback) = 0;
	virtual IGraphicsContext* getGraphicsContext() = 0;
	virtual IInputHandler* getInputHandler() = 0;
};
