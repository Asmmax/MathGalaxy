#pragma once
#include <string>

class Texture
{
private:
	std::string _fileName;
	unsigned int _textureHandle;
	int _textureUnit;

public:
	Texture(const std::string& fileName);

	void init();
	void apply(int textureUnit);
	void clear();

private:
	static unsigned char* loadPixels(const std::string& fName, int& width, int& height);
};
