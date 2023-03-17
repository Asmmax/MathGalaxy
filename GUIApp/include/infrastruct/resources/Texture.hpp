#pragma once

class ITextureImpl;
struct TextureData;

class Texture
{
private:
	ITextureImpl* _impl;
	int _textureUnit;
	int _width;
	int _height;

public:
	Texture(ITextureImpl* textureImpl);
	~Texture();

	void init(const TextureData& data);
	void apply(int textureUnit);
	void clear();

	void updateData(const TextureData& data);
	void resize(int width, int height);
};
