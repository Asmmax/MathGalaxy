#pragma once
#include <memory>

class Window;
class MainView;
class CameraView;
class Scene;


class RenderLoop
{
private:
	std::shared_ptr<Scene> _scene;
	std::shared_ptr<CameraView> _cameraView;
	std::shared_ptr<MainView> _mainView;
	Window* _window{};

public:
	RenderLoop(Window* window, const std::shared_ptr<MainView>& mainView, const std::shared_ptr<CameraView>& cameraView, const std::shared_ptr<Scene>& scene);

	void run();
};
