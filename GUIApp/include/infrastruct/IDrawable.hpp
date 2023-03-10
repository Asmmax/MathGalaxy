#pragma once
#include <memory>

class DrawContext;
class IGraphicsContext;

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void init(const std::weak_ptr<IGraphicsContext>& context) = 0;
	virtual void predraw(DrawContext& context) = 0;
	virtual void draw(const DrawContext& context) = 0;
};