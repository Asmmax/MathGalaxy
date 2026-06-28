#include "RenderLoop.hpp"

#include "CameraView.hpp"
#include "MainView.hpp"
#include "RenderQueue.hpp"
#include "Window.hpp"
#include "drawables/Scene.hpp"


RenderLoop::RenderLoop(Window* window, const std::shared_ptr<MainView>& mainView,
                       const std::shared_ptr<CameraView>& cameraView, const std::shared_ptr<Scene>& scene):
	_window(window),
	_mainView(mainView),
	_cameraView(cameraView),
	_scene(scene)
{
}

void RenderLoop::run()
{
	RenderData frameData;
	RenderQueue renderQueue;

	while (!_window->isDone()) {
		_window->handle();

		renderQueue.clear();
		frameData.clear();

		_scene->draw(renderQueue, frameData);

		renderQueue.sort();

		_cameraView->render(renderQueue, frameData);
		_mainView->render();

		_window->render();
		_window->swapBuffers();
	}
}
