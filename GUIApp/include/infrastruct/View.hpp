#pragma once
#include "infrastruct/DrawState.hpp"
#include <type_traits>
#include <cstdint>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Model;
class IGraphicsContext;
class IViewImpl;

class View
{
public:
	typedef std::conditional<sizeof(void*) == sizeof(std::int32_t), std::int32_t, std::int64_t>::type TextureIdType;

private:
	IViewImpl* _impl;
	IGraphicsContext* _context;
	int _width;
	int _height;
	glm::vec3 _background;
	glm::mat4 _matrix;
	DrawStatePool _statePool;

	bool _isResized;

public:
	View(IViewImpl* viewImpl, int width, int height);
	~View();

	void init(IGraphicsContext* context);
	void render(Model* model);
	void setSize(int width, int height);

	void setMatrix(const glm::mat4& matrix) { _matrix = matrix; }
	const glm::mat4& getMatrix() const { return _matrix; }

	TextureIdType getFBOTextureId() const;

	void setBackground(const glm::vec3& color) { _background = color; }
	const glm::vec3& getBackground() const { return _background; }

private:
	void resizeBuffer();
};
