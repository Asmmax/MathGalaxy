#pragma once
#include <type_traits>
#include <cstdint>
#include <memory>

class IDrawable;
class Transform;

class View
{
public:
	typedef std::conditional<sizeof(void*) == sizeof(std::int32_t), std::int32_t, std::int64_t>::type TextureIdType;

	struct Color {
		float r;
		float g;
		float b;
		float a;
	};

private:
	int _width;
	int _height;
	Color _background;
	std::shared_ptr<Transform> _target;

	unsigned int _fboTextureId;
	unsigned int _fboId;
	unsigned int _fboDepthBufferId;

	bool _isResized;

public:
	View(int width, int height, const std::shared_ptr<Transform>& target = nullptr);

	void init();
	void render(IDrawable* drawable);
	void setSize(int width, int height);

	void setTarget(const std::shared_ptr<Transform>& target) { _target = target; }
	TextureIdType getFBOTextureId() const { return static_cast<TextureIdType>(_fboTextureId); }

	void setBackground(const Color& color) { _background = color; }
	const Color& getBackground() const { return _background; }

private:
	void resizeBuffer();
};
