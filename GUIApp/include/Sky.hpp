#pragma once
#include <memory>
#include <glm/vec3.hpp>

class AMesh;
class DrawContext;
class SkyMaterial;
class Shader;
class Texture;

class Sky
{
private:
	glm::vec3 _ambientColor;
	std::shared_ptr<AMesh> _mesh;
	std::shared_ptr<SkyMaterial> _material;
	float _size;

public:
	Sky(const std::shared_ptr<AMesh>& mesh, const std::shared_ptr<Shader>& shader);

	void setBaseColor(const glm::vec3& color);
	void setBaseTexture(const std::shared_ptr<Texture>& texture);
	void setAmbientColor(const glm::vec3& color);
	void setMesh(const std::shared_ptr<AMesh>& mesh);

	void init();
	void predraw(DrawContext& context);
	void draw(DrawContext& context);
};
