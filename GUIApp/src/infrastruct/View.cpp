#include "infrastruct/View.hpp"
#include "infrastruct/Model.hpp"
#include "infrastruct/DrawState.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "infrastruct/IViewImpl.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

View::View(IViewImpl* viewImpl, int width, int height):
	_impl(viewImpl),
	_context(nullptr),
	_width(width),
	_height(height),
	_background(0.5f, 0.5f, 0.5f),
	_matrix(),
	_statePool(10),
	_isResized(false)
{
}

View::~View()
{
	_impl->terminate();
	delete _impl;
}

void View::init(IGraphicsContext* context)
{
	_context = context;

	if (!_context) {
		return;
	}
	_context->makeCurrent();

	_impl->init();
	_impl->resizeBuffer(_width, _height);
}

void View::render(Model* model)
{
	if (!_context) {
		return;
	}
	_context->makeCurrent();

	resizeBuffer();

	_impl->beginDraw(_width, _height, _background);

	_statePool.push();

	auto& state = _statePool.get();
	state.add("ViewMatrix", _matrix);
	state.add("ProjectionMatrix", glm::perspective(45.0f, _width / (float)_height, 0.01f, 1000.0f));

	if (model) {
		model->predraw(_statePool);
		model->draw(_statePool);
	}

	_statePool.pop();

	_impl->endDraw();
}

void View::setSize(int width, int height)
{
	if (_width != width || _height != height) {
		_width = width;
		_height = height;
		_isResized = true;
	}
}

View::TextureIdType View::getFBOTextureId() const
{ 
	return static_cast<TextureIdType>(_impl->getFBOTextureId());
}

void View::resizeBuffer()
{
	if (!_isResized) {
		return;
	}

	_impl->resizeBuffer(_width, _height);

	_isResized = false;
}
