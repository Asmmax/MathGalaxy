#pragma once
#include "gui/menu/AMenuItem.hpp"
#include <memory>

class AWidget;

class MenuItemEnabler : public AMenuItem
{
private:
	std::weak_ptr<AWidget> _widget;
public:
	MenuItemEnabler(const std::string& name, const std::weak_ptr<AWidget>& widget);

protected:
	void click() override;
};
