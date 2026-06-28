#pragma once
#include <memory>

class RenderData;
class RenderQueue;
class Transform;
class Camera;
class CelestialSystem;

class Scene
{
private:
	std::unique_ptr<CelestialSystem> _celSystem;
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Transform> _root;

public:
	Scene();
	~Scene();

	void setCelestialSystem(std::unique_ptr<CelestialSystem> celSystem);
	void setCamera(const std::shared_ptr<Camera>& camera);

	std::shared_ptr<Transform> getRoot() {return _root;}

	void draw(RenderQueue& renderQueue, RenderData& frameData);
};
