#pragma once
#include <glm/vec3.hpp>

class IViewImpl
{
public:
	virtual ~IViewImpl() {}

	virtual void init() = 0;
	virtual void terminate() = 0;

	virtual void beginDraw(int width, int height, const glm::vec3& background) = 0;
	virtual void endDraw() = 0;
	virtual void resizeBuffer(int width, int height) = 0;

	virtual unsigned int getFBOTextureId() const = 0;
};
