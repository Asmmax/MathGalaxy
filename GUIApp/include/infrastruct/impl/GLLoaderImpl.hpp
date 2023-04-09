#pragma once
#include "infrastruct/ILoaderImpl.hpp"
#include "infrastruct/impl/GLMeshImpl.hpp"
#include "infrastruct/impl/GLTextureImpl.hpp"
#include "infrastruct/impl/GLShaderImpl.hpp"
#include "infrastruct/PoolAllocator.hpp"

class GLLoaderImpl : public ILoaderImpl
{
	PoolAllocator<GLMeshImpl> _meshAllocator;
	PoolAllocator<GLTextureImpl> _textureAllocator;
	PoolAllocator<GLShaderImpl> _shaderAllocator;

public:
	GLLoaderImpl(size_t poolSize = 100);

	IMeshImpl* createMesh() override;
	ITextureImpl* createTexture() override;
	IShaderImpl* createShader() override;
};
