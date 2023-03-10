#pragma once
#include "infrastruct/IDrawable.hpp"
#include <memory>
#include <glm/vec3.hpp>

class AMesh;
class SkyMaterial;
class Shader;
class Texture;

class Sky : public IDrawable
{
private:
	glm::vec3 _ambientColor;
	std::shared_ptr<AMesh> _mesh;
	std::shared_ptr<SkyMaterial> _material;
	float _size;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	Sky(const std::shared_ptr<AMesh>& mesh, const std::shared_ptr<Shader>& shader);

	void setBaseColor(const glm::vec3& color);
	void setBaseTexture(const std::shared_ptr<Texture>& texture);
	void setAmbientColor(const glm::vec3& color);
	void setMesh(const std::shared_ptr<AMesh>& mesh);

	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void deinit();

	void predraw(DrawContext& context) override;
	void draw(const DrawContext& context) override;
};
