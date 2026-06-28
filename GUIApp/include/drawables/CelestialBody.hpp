#pragma once
#include <memory>

class Shader;
class Material;
class Mesh;
class Transform;
class Light;
class RenderData;
class RenderQueue;

class CelestialBody
{
private:
	Shader* _shader{};
	Material* _material{};
	Mesh* _mesh{};
	std::shared_ptr<Transform> _transform;
	std::unique_ptr<Light> _light;

public:
	CelestialBody();
	~CelestialBody();

	void setShader(Shader* shader);
	void setMaterial(Material* material);
	void setMesh(Mesh* mesh);
	void setLight(std::unique_ptr<Light> light);

	std::shared_ptr<Transform> getTransform() {return _transform;}
	Material* getMaterial() {return _material;}

	void preDraw(RenderData& frameData);
	void draw(RenderQueue& renderQueue);
};
