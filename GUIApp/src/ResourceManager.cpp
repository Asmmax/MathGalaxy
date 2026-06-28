#include "ResourceManager.hpp"

#include "Loader.hpp"
#include "Path.hpp"
#include "resources/MeshData.hpp"
#include "resources/ShaderData.hpp"
#include "resources/TextureData.hpp"


ResourceManager::~ResourceManager()
{
	if (_loader){
		_loader->release(_sphereMesh);
		_loader->release(_skyTexture);
		_loader->release(_starShader);
		_loader->release(_planetShader);
		_loader->release(_skyShader);
	}
}

void ResourceManager::load(Loader* loader)
{
	_loader = loader;

	Path path("settings.dat");

	auto sphereMeshData = createSphere(1.0f, 24, 48);
	_sphereMesh = loader->loadMesh(sphereMeshData);

	auto starVert = loadShader(path.find("shaders/star.vert"));
	auto starFrag = loadShader(path.find("shaders/star.frag"));
	_starShader = loader->loadShader(starVert, starFrag);

	auto planetVert = loadShader(path.find("shaders/planet.vert"));
	auto planetFrag = loadShader(path.find("shaders/planet.frag"));
	_planetShader = loader->loadShader(planetVert, planetFrag);

	auto skyVert = loadShader(path.find("shaders/sky.vert"));
	auto skyFrag = loadShader(path.find("shaders/sky.frag"));
	_skyShader = loader->loadShader(skyVert, skyFrag);

	auto skyTextureData = readTexture(path.find("textures/sky.png"));
	_skyTexture = loader->loadTexture(skyTextureData);
}

Material* ResourceManager::createMaterial()
{
	if (!_loader)
	{
		return nullptr;
	}

	Material* newMaterial = _loader->createMaterial();
	_materials.push_back(newMaterial);
	return newMaterial;
}

Material* ResourceManager::getMaterial(int idx) const
{
	return _materials[idx];
}

int ResourceManager::getMaterialCount() const
{
	return static_cast<int>(_materials.size());
}
