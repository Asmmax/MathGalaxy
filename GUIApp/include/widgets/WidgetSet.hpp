#pragma once
#include "IWidget.hpp"
#include <memory>
#include <vector>

class WidgetSet : public IWidget
{
private:
	std::vector<std::shared_ptr<IWidget>> _children;
public:
	void addChild(const std::shared_ptr<IWidget>& child);
	void setup() override;
};
