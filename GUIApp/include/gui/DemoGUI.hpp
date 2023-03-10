#pragma once
#include "infrastruct/IGUI.hpp"

class IGraphicsContext;

class DemoGUI : public IGUI
{
private:
	std::weak_ptr<IGraphicsContext> _graphicsContext;
public:
	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void setup() override;
};
