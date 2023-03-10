#pragma once
#include "infrastruct/IDrawable.hpp"
#include "glm/vec3.hpp"
#include <memory>
#include <string>
#include <map>

class Shader;
class Texture;
class IGraphicsContext;

class AMaterial
{
private:
	std::shared_ptr<Shader> _shader;
	std::map<std::string, std::shared_ptr<Texture>> _textures;
	std::weak_ptr<IGraphicsContext> _graphicsContext;

public:
	AMaterial(const std::shared_ptr<Shader>& shader);
	virtual ~AMaterial() {}

	void setShader(const std::shared_ptr<Shader>& shader);

	void init(const std::weak_ptr<IGraphicsContext>& context);
	void deinit();
	void apply(const DrawContext& context);
	void clear();

protected:
	virtual void applyImpl() = 0;

	void addTexture(const std::string& name, const std::shared_ptr<Texture>& texture);
	void removeTexture(const std::string& name);

	const std::shared_ptr<Shader>& getShader() const { return _shader; }

private:
};
