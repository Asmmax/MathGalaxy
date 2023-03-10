#pragma once
#include <memory>

class IGraphicsContext;

class IGUI
{
public:
	virtual ~IGUI() {}
	virtual void init(const std::weak_ptr<IGraphicsContext>& context) = 0;
	virtual void setup() = 0;
};
