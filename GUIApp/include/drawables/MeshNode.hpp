#pragma once
#include "drawables/Node.hpp"
#include "glm/glm.hpp"
#include <vector>

class AMaterial;
class AMesh;

class MeshNode : public Node
{
private:
	std::shared_ptr<AMesh> _mesh;
	std::shared_ptr<AMaterial> _material;
public:
	void setMesh(const std::shared_ptr<AMesh>& mesh);
	void setMaterial(const std::shared_ptr<AMaterial>& material);

	void init() override;
	void predraw(DrawContext& context) override;
	void draw(DrawContext& context) override;
};
