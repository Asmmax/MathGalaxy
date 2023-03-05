#pragma once
#include "IDrawable.hpp"
#include "glm/vec3.hpp"
#include <memory>
#include <string>
#include <map>

class Shader;
class Texture;

class AMaterial
{
private:
	std::shared_ptr<Shader> _shader;
	std::map<std::string, std::shared_ptr<Texture>> _textures;
	bool _isInited;

public:
	AMaterial(const std::shared_ptr<Shader>& shader);
	virtual ~AMaterial() {}

	void setShader(const std::shared_ptr<Shader>& shader);

	void apply(const DrawContext& context);
	void clear();

protected:
	virtual void applyImpl() = 0;

	void addTexture(const std::string& name, const std::shared_ptr<Texture>& texture);
	void removeTexture(const std::string& name);

	const std::shared_ptr<Shader>& getShader() const { return _shader; }

private:
	void init();
};
