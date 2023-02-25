#pragma once
#include "drawables/Node.hpp"
#include "glm/glm.hpp"
#include <vector>

class Material;
class AMesh;

class MeshNode : public Node
{
private:
	std::shared_ptr<AMesh> _mesh;
	std::shared_ptr<Material> _material;
public:
	void setMesh(const std::shared_ptr<AMesh>& mesh);
	void setMaterial(const std::shared_ptr<Material>& material);

	void init() override;
	void predraw(DrawContext& context) override;
	void draw(DrawContext& context) override;
};
