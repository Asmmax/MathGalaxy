#pragma once
#include <vector>


class Material;
class Loader;
class Texture;
class Shader;
class Mesh;

class ResourceManager
{
private:
	Mesh* _sphereMesh{};
	Shader* _starShader{};
	Shader* _planetShader{};
	Shader* _skyShader{};
	Texture* _skyTexture{};
	Loader* _loader{};
	std::vector<Material*> _materials;

public:
	~ResourceManager();

	void load(Loader* loader);

	Mesh* getSphereMesh() const {return _sphereMesh;}
	Shader* getStarShader() const {return _starShader;}
	Shader* getPlanetShader() const {return _planetShader;}
	Shader* getSkyShader() const {return _skyShader;}
	Texture* getSkyTexture() const {return _skyTexture;}

	Material* createMaterial();
	Material* getMaterial(int idx) const;
	int getMaterialCount() const;
};
