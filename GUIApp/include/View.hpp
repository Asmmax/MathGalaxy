#pragma once
#include <type_traits>
#include <cstdint>
#include <memory>
#include <glm/vec3.hpp>

class IDrawable;
class Transform;
class Sky;

class View
{
public:
	typedef std::conditional<sizeof(void*) == sizeof(std::int32_t), std::int32_t, std::int64_t>::type TextureIdType;

private:
	int _width;
	int _height;
	glm::vec3 _background;
	std::shared_ptr<Transform> _target;
	std::shared_ptr<Sky> _sky;

	unsigned int _fboTextureId;
	unsigned int _fboId;
	unsigned int _fboDepthBufferId;

	bool _isResized;

public:
	View(int width, int height, const std::shared_ptr<Transform>& target = nullptr);

	void init();
	void render(IDrawable* drawable);
	void setSize(int width, int height);
	void setSky(const std::shared_ptr<Sky>& sky);

	void setTarget(const std::shared_ptr<Transform>& target) { _target = target; }
	TextureIdType getFBOTextureId() const { return static_cast<TextureIdType>(_fboTextureId); }

	void setBackground(const glm::vec3& color) { _background = color; }
	const glm::vec3& getBackground() const { return _background; }

private:
	void resizeBuffer();
};
