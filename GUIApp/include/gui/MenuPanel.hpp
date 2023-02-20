#pragma once
#include <memory>
#include <vector>

class MenuList;

class MenuPanel
{
private:
	std::vector<std::shared_ptr<MenuList>> _lists;
public:
	void setup();
	void addList(const std::shared_ptr<MenuList>& list);
};
