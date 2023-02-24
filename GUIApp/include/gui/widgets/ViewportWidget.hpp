#pragma once
#include "gui/AWidget.hpp"
#include <memory>

class View;

class ViewportWidget : public AWidget
{
private:
	std::weak_ptr<View> _view;

public:
	ViewportWidget(const std::string& name, int width, int height, const std::weak_ptr<View>& view);

protected:
	void setupContent() override;
};
