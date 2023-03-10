#include "infrastruct/View.hpp"
#include "infrastruct/IDrawable.hpp"
#include "infrastruct/DrawContext.hpp"
#include "infrastruct/IGraphicsContext.hpp"
#include "gl/gl_core_4_3.hpp"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

View::View(int width, int height):
	_width(width),
	_height(height),
	_background(0.5f, 0.5f, 0.5f),
	_matrix(),
	_fboTextureId(0),
	_fboId(0),
	_fboDepthBufferId(0),
	_isResized(false)
{
}

void View::init(const std::weak_ptr<IGraphicsContext>& context)
{
	auto sharedContext = context.lock();
	if (_graphicsContext.lock() == sharedContext) {
		return;
	}

	_graphicsContext = context;

	if (!sharedContext) {
		return;
	}
	sharedContext->makeCurrent();

	gl::GenFramebuffers(1, &_fboId);
	gl::BindFramebuffer(gl::FRAMEBUFFER, _fboId);

	gl::GenTextures(1, &_fboTextureId);
	gl::BindTexture(gl::TEXTURE_2D, _fboTextureId);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, _width, _height, 0, gl::RGBA, gl::UNSIGNED_BYTE, nullptr);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);

	gl::FramebufferTexture2D(gl::FRAMEBUFFER, gl::COLOR_ATTACHMENT0, gl::TEXTURE_2D, _fboTextureId, 0);

	gl::GenRenderbuffers(1, &_fboDepthBufferId);
	gl::BindRenderbuffer(gl::RENDERBUFFER, _fboDepthBufferId);
	gl::RenderbufferStorage(gl::RENDERBUFFER, gl::DEPTH_COMPONENT, _width, _height);
	gl::FramebufferRenderbuffer(gl::FRAMEBUFFER, gl::DEPTH_ATTACHMENT, gl::RENDERBUFFER, _fboDepthBufferId);

	gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
}

void View::render(IDrawable* drawable)
{
	if (_isResized) {
		resizeBuffer();
	}

	gl::BindFramebuffer(gl::FRAMEBUFFER, _fboId);
	gl::Viewport(0, 0, _width, _height);

	gl::ClearColor(_background.r, _background.g, _background.b, 1.0f);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	DrawContext context;

	context.add("ViewMatrix", _matrix);
	context.add("ProjectionMatrix", glm::perspective(45.0f, _width / (float)_height, 0.01f, 1000.0f));

	if (_sky) {
		_sky->predraw(context);
	}

	if (drawable) {
		drawable->predraw(context);
	}

	if (_sky) {
		_sky->draw(context);
	}

	if (drawable) {
		drawable->draw(context);
	}

	gl::BindFramebuffer(gl::FRAMEBUFFER, 0);
}

void View::setSize(int width, int height)
{
	if (_width != width || _height != height) {
		_width = width;
		_height = height;
		_isResized = true;
	}
}

void View::setSky(const std::shared_ptr<IDrawable>& sky)
{
	_sky = sky;

	assert(!_graphicsContext.expired());
	if (_graphicsContext.expired()) {
		return;
	}

	if (_sky) {
		_sky->init(_graphicsContext);
	}
}

void View::resizeBuffer()
{
	gl::BindFramebuffer(gl::FRAMEBUFFER, _fboId);

	gl::BindTexture(gl::TEXTURE_2D, _fboTextureId);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGBA, _width, _height, 0, gl::RGBA, gl::UNSIGNED_BYTE, nullptr);
	gl::FramebufferTexture2D(gl::FRAMEBUFFER, gl::COLOR_ATTACHMENT0, gl::TEXTURE_2D, _fboTextureId, 0);

	gl::BindRenderbuffer(gl::RENDERBUFFER, _fboDepthBufferId);
	gl::RenderbufferStorage(gl::RENDERBUFFER, gl::DEPTH_COMPONENT, _width, _height);
	gl::FramebufferRenderbuffer(gl::FRAMEBUFFER, gl::DEPTH_ATTACHMENT, gl::RENDERBUFFER, _fboDepthBufferId);

	gl::BindFramebuffer(gl::FRAMEBUFFER, 0);

	_isResized = false;
}
