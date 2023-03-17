#include "infrastruct/impl/GLLoaderImpl.hpp"
#include <cstdint>

IMeshImpl* GLLoaderImpl::createMesh()
{
	return new GLMeshImpl();
}

ITextureImpl* GLLoaderImpl::createTexture()
{
	return new GLTextureImpl();
}

IShaderImpl* GLLoaderImpl::createShader()
{
	return new GLShaderImpl();
}
