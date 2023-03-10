#pragma once
#include <memory>

class IGraphicsContext;
class IInputHandler;

class IWindowImpl
{
public:
	virtual ~IWindowImpl() {}

	virtual void init() = 0;
	virtual void terminate() = 0;
	virtual bool isDone() = 0;
	virtual void handle() = 0;
	virtual std::weak_ptr<IGraphicsContext> getGraphicsContext() = 0;
	virtual std::weak_ptr<IInputHandler> getInputHandler() = 0;
};
