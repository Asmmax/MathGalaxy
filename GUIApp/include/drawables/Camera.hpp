#pragma once
#include <memory>

class Shader;
class Material;
class Mesh;
class Transform;
class CameraController;
class Window;
class RenderQueue;

class Camera
{
private:
	Shader* _skyShader{};
	Material* _skyMaterial{};
	Mesh* _skyMesh{};
	std::shared_ptr<Transform> _cameraTarget;
	std::shared_ptr<Transform> _cameraEye;
	std::shared_ptr<CameraController> _controller;
public:
	Camera();

	void initController(Window* window);

	void setSkyShader(Shader* skyShader);
	void setSkyMaterial(Material* skyMaterial);
	void setSkyMesh(Mesh* skyMesh);

	std::shared_ptr<Transform> getTargetTransform() {return _cameraTarget;}
	std::shared_ptr<Transform> getEyeTransform() {return _cameraEye;}

	void draw(RenderQueue& renderQueue);
};
