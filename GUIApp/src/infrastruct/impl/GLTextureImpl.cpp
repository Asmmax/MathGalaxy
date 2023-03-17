#include "infrastruct/impl/GLTextureImpl.hpp"
#include "infrastruct/resources/TextureData.hpp"
#include "gl/gl_core_4_3.hpp"

GLTextureImpl::GLTextureImpl():
	_textureHandle(0)
{
}

void GLTextureImpl::init()
{
	gl::GenTextures(1, &_textureHandle);

	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);

	gl::BindTexture(gl::TEXTURE_2D, 0);
}

void GLTextureImpl::terminate()
{
	gl::DeleteTextures(1, &_textureHandle);
	_textureHandle = 0;
}

void GLTextureImpl::applyTo(int texUnit)
{
	gl::ActiveTexture(gl::TEXTURE0 + texUnit);
	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);
}

void GLTextureImpl::clear(int texUnit)
{
	gl::ActiveTexture(gl::TEXTURE0 + texUnit);
	gl::BindTexture(gl::TEXTURE_2D, 0);
}

void GLTextureImpl::updateData(const TextureData& data)
{
	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, data.width, data.height, 0, gl::RGBA, gl::UNSIGNED_BYTE, data.data.data());
}

void GLTextureImpl::resize(int width, int height)
{
	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, width, height, 0, gl::RGBA, gl::UNSIGNED_BYTE, nullptr);
}
