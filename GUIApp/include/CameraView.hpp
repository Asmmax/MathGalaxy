#pragma once
#include <memory>

class RenderData;
class RenderQueue;
class Window;
class Camera;
class Loader;
class View;
class Texture;


class CameraView
{
private:
	Texture* _cameraTex{};
	View* _cameraView{};
	Loader* _loader{};
	std::shared_ptr<Camera> _cameraObj;

public:
	CameraView(Window* window, const std::shared_ptr<Camera>& cameraObj);
	~CameraView();

	View* getView() { return _cameraView; }

	void render(const RenderQueue& renderQueue, const RenderData& frameData);
};
