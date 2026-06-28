#include "MainView.hpp"

#include "Loader.hpp"
#include "View.hpp"
#include "Window.hpp"
#include "gui/GUI.hpp"


MainView::MainView(Window* window, const std::shared_ptr<GUI>& gui):
	_window(window),
	_gui(gui)
{
	Loader* loader = _window->getLoader();
	_mainViewTex = loader->createTexture(512, 512);
	_mainView = window->creteView(_mainViewTex);
	window->setMainView(_mainView);
}

MainView::~MainView()
{
	if (_window)
	{
		Loader* loader = _window->getLoader();
		loader->release(_mainViewTex);
	}
}

void MainView::render()
{
	int frameWidth = 0;
	int frameHeight = 0;
	_window->getFrameSize(frameWidth, frameHeight);
	_mainView->setSize(frameWidth, frameHeight);

	_mainView->beginRender();
	if (!_imguiInited) {
		_gui->init();
		_imguiInited = true;
	}
	_mainView->setupImgui();
	_gui->setup();
	_mainView->renderImgui();
	_mainView->endRender();
}
