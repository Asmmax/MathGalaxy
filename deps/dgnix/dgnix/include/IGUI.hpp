#pragma once
#include <memory>

class IGUI
{
public:
	virtual ~IGUI() {}
	virtual void init() = 0;
	virtual void setup() = 0;
};