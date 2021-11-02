#pragma once

class IDrawable
{
public:
	virtual ~IDrawable() {}
	virtual void draw() = 0;
};