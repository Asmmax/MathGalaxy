#pragma once
#include "gui/AWidget.hpp"
#include <memory>

class View;

class ViewportWidget : public AWidget
{
private:
	View* _view;

public:
	ViewportWidget(const std::string& name, int width, int height, View* view);

protected:
	void setupContent() override;
};
