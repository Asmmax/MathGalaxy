#pragma once

class IWidget
{
public:
	virtual ~IWidget() {}
	virtual void setup() = 0;
};