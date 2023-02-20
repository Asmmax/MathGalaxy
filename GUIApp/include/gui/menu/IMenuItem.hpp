#pragma once

class IMenuItem
{
public:
	virtual ~IMenuItem() {}
	virtual void setup() = 0;
};
