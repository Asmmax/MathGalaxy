#pragma once
#include "IMenuItem.hpp"
#include <string>

class AMenuItem : public IMenuItem
{
private:
	std::string _name;
	std::string _shortcut;
	bool _isEnabled;

public:
	AMenuItem(const std::string& name);

	void enable();
	void disable();

	void setup() override;

protected:
	virtual void click() = 0;
};
