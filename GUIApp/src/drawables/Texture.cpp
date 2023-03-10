#include "drawables/Texture.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "gl/gl_core_4_3.hpp"
#include <iostream>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& fileName):
	_fileName(fileName),
	_textureHandle(0),
	_textureUnit(-1)
{
}

void Texture::init(const std::weak_ptr<IGraphicsContext>& context)
{
	auto sharedContext = context.lock();
	if (_graphicsContext.lock() == sharedContext) {
		return;
	}

	deinit();
	_graphicsContext = context;

	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	if (_textureHandle != 0) {
		return;
	}

	int width = 0;
	int height = 0;
	unsigned char* data = Texture::loadPixels(_fileName, width, height);
	if (data == nullptr) {
		std::cerr << "Cannot open \"" << _fileName << "\" as TGA\n";
		return;
	}

	gl::GenTextures(1, &_textureHandle);

	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);

	gl::TexStorage2D(gl::TEXTURE_2D, 1, gl::RGBA8, width, height);
	gl::TexSubImage2D(gl::TEXTURE_2D, 0, 0, 0, width, height, gl::RGBA, gl::UNSIGNED_BYTE, data);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);

	gl::BindTexture(gl::TEXTURE_2D, 0);

	stbi_image_free(data);
}

void Texture::deinit()
{
	auto sharedContext = _graphicsContext.lock();
	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	gl::DeleteTextures(1, &_textureHandle);
	_textureHandle = 0;

	_graphicsContext.reset();
}

void Texture::apply(int textureUnit)
{
	gl::ActiveTexture(gl::TEXTURE0 + textureUnit);
	gl::BindTexture(gl::TEXTURE_2D, _textureHandle);
	_textureUnit = textureUnit;
}

void Texture::clear()
{
	if (_textureUnit < 0) {
		return;
	}
	gl::ActiveTexture(gl::TEXTURE0 + _textureUnit);
	gl::BindTexture(gl::TEXTURE_2D, 0);
	_textureUnit = -1;
}

unsigned char* Texture::loadPixels(const std::string& fName, int& width, int& height) {
	int bytesPerPix;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fName.c_str(), &width, &height, &bytesPerPix, 4);
	return data;
}
