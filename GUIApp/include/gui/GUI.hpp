#pragma once
#include "IGUI.hpp"
#include <memory>
#include <vector>

class AWidget;
class MenuPanel;

class GUI : public IGUI
{
private:
	std::vector<std::shared_ptr<AWidget>> _children;
	std::shared_ptr<MenuPanel> _menu;
public:
	void addWidget(const std::shared_ptr<AWidget>& child);
	void setMenu(const std::shared_ptr<MenuPanel>& menu);
	void setup() override;
};
