#pragma once
#include "infrastruct/IGUI.hpp"
#include <memory>
#include <vector>

class AWidget;
class MenuPanel;
class IGraphicsContext;

class GUI : public IGUI
{
private:
	std::vector<std::shared_ptr<AWidget>> _children;
	std::shared_ptr<MenuPanel> _menu;
	std::weak_ptr<IGraphicsContext> _graphicsContext;
public:
	void addWidget(const std::shared_ptr<AWidget>& child);
	void setMenu(const std::shared_ptr<MenuPanel>& menu);

	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void setup() override;
};
