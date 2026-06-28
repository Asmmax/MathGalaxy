#include "CameraView.hpp"

#include "View.hpp"
#include "Window.hpp"
#include "drawables/Camera.hpp"
#include "drawables/Transform.hpp"


CameraView::CameraView(Window* window, const std::shared_ptr<Camera>& cameraObj):
	_cameraObj(cameraObj)
{
	_loader = window->getLoader();
	_cameraTex = _loader->createTexture(512, 512);
	_cameraView = window->creteView(_cameraTex);
}

CameraView::~CameraView()
{
	if (_loader)
	{
		_loader->release(_cameraTex);
	}
}

void CameraView::render(const RenderQueue& renderQueue, const RenderData& frameData)
{
	const auto viewMatrix = glm::inverse(_cameraObj->getEyeTransform()->getGlobalMatrix());

	_cameraView->beginRender();
	_cameraView->render(renderQueue, frameData, viewMatrix);
	_cameraView->endRender();
}
