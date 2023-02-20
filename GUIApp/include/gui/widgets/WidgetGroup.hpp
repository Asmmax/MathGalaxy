#pragma once
#include "gui/AWidget.hpp"
#include <memory>
#include <vector>

class WidgetGroup : public AWidget
{
private:
	std::vector<std::shared_ptr<AWidget>> _children;

public:
	WidgetGroup(const std::string& name);

	void addChild(const std::shared_ptr<AWidget>& widget);

protected:
	void draw() override;
};
