#pragma once
#include "infrastruct/resources/ITextureImpl.hpp"

class GLTextureImpl : public ITextureImpl
{
private:
	unsigned int _textureHandle;
public:
	GLTextureImpl();

	void init() override;
	void terminate() override;

	void applyTo(int texUnit) override;
	void clear(int texUnit) override;

	void updateData(const TextureData& data) override;
	void resize(int width, int height) override;
};
