#pragma once
#include "infrastruct/ILoaderImpl.hpp"
#include "infrastruct/impl/GLMeshImpl.hpp"
#include "infrastruct/impl/GLTextureImpl.hpp"
#include "infrastruct/impl/GLShaderImpl.hpp"
#include <vector>

class GLLoaderImpl : public ILoaderImpl
{
public:
	IMeshImpl* createMesh() override;
	ITextureImpl* createTexture() override;
	IShaderImpl* createShader() override;
};
