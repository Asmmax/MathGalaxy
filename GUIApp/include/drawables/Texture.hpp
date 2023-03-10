#pragma once
#include <string>
#include <memory>

class IGraphicsContext;

class Texture
{
private:
	std::string _fileName;
	unsigned int _textureHandle;
	int _textureUnit;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	Texture(const std::string& fileName);

	void init(const std::weak_ptr<IGraphicsContext>& context);
	void deinit();
	void apply(int textureUnit);
	void clear();

private:
	static unsigned char* loadPixels(const std::string& fName, int& width, int& height);
};
