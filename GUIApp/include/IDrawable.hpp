#pragma once

class DrawContext;

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void init() = 0;
	virtual void predraw(DrawContext& context) = 0;
	virtual void draw(DrawContext& context) = 0;
};