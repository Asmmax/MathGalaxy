#pragma once
#include <type_traits>
#include <cstdint>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class IDrawable;
class IGraphicsContext;

class View
{
public:
	typedef std::conditional<sizeof(void*) == sizeof(std::int32_t), std::int32_t, std::int64_t>::type TextureIdType;

private:
	int _width;
	int _height;
	glm::vec3 _background;
	glm::mat4 _matrix;
	std::shared_ptr<IDrawable> _sky;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

	unsigned int _fboTextureId;
	unsigned int _fboId;
	unsigned int _fboDepthBufferId;

	bool _isResized;

public:
	View(int width, int height);

	void init(const std::weak_ptr<IGraphicsContext>& context);
	void render(IDrawable* drawable);
	void setSize(int width, int height);
	void setSky(const std::shared_ptr<IDrawable>& sky);

	void setMatrix(const glm::mat4& matrix) { _matrix = matrix; }
	const glm::mat4& getMatrix() const { return _matrix; }

	TextureIdType getFBOTextureId() const { return static_cast<TextureIdType>(_fboTextureId); }

	void setBackground(const glm::vec3& color) { _background = color; }
	const glm::vec3& getBackground() const { return _background; }

private:
	void resizeBuffer();
};
