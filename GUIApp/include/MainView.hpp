#pragma once
#include <memory>

class GUI;
class Window;
class View;
class Texture;


class MainView
{
private:
	Texture* _mainViewTex{};
	View* _mainView{};
	Window* _window{};
	std::shared_ptr<GUI> _gui;
	bool _imguiInited{false};
public:
	MainView(Window* window, const std::shared_ptr<GUI>& gui);
	~MainView();

	void render();
};
