#pragma once
#include "drawables/nodes/Node.hpp"
#include "glm/glm.hpp"
#include <vector>

class AMaterial;
class AMesh;

class MeshNode : public Node
{
private:
	std::shared_ptr<AMesh> _mesh;
	std::shared_ptr<AMaterial> _material;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	void setMesh(const std::shared_ptr<AMesh>& mesh);
	void setMaterial(const std::shared_ptr<AMaterial>& material);

	void init(const std::weak_ptr<IGraphicsContext>& context) override;
	void deinit() override;
	void predraw(DrawContext& context) override;
	void draw(const DrawContext& context) override;
};
