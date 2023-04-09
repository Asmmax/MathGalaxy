#pragma once
#include "infrastruct/resources/ITextureImpl.hpp"
#include "infrastruct/PoolAllocator.hpp"

class GLTextureImpl : public ITextureImpl
{
private:
	unsigned int _textureHandle;
	PoolAllocator<GLTextureImpl>* _allocator;

public:
	GLTextureImpl(PoolAllocator<GLTextureImpl>* allocator);

	void init() override;
	void terminate() override;
	void free() override;

	void applyTo(int texUnit) override;
	void clear(int texUnit) override;

	void updateData(const TextureData& data) override;
	void resize(int width, int height) override;
};
