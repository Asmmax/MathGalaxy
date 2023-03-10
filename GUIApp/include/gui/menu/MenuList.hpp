#pragma once
#include "gui/menu/IMenuItem.hpp"
#include <memory>
#include <vector>
#include <string>

class MenuList
{
private:
	std::string _name;
	std::vector<std::shared_ptr<IMenuItem>> _items;
	bool _isEnabled;

private:
	class Separator : public IMenuItem
	{
	public:
		void setup();
	};

public:
	MenuList(const std::string& name);

	void enable();
	void disable();

	void setup();
	void addItem(const std::shared_ptr<IMenuItem>& item);
	void addSeparator();
};
