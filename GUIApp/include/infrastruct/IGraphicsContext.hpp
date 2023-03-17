#pragma once
#include <utility>

class ILoaderImpl;

class IGraphicsContext
{
public:
	struct ISize
	{
		int width = 1;
		int height = 1;
	};

	virtual ~IGraphicsContext() {}

	virtual void init() = 0;
	virtual void terminate() = 0;
	virtual void makeCurrent() = 0;
	virtual ISize getFramebufferSize() = 0;
	virtual void swapBuffers() = 0;
	virtual void setupImgui() = 0;
	virtual void renderImgui() = 0;

	virtual ILoaderImpl* createLoader() = 0;
};
