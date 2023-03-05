#pragma once
#include "IDrawable.hpp"
#include "glm/vec3.hpp"
#include <memory>

class Shader;

class AMaterial
{
private:
	std::shared_ptr<Shader> _shader;

public:
	AMaterial(const std::shared_ptr<Shader>& shader);
	virtual ~AMaterial() {}

	void setShader(const std::shared_ptr<Shader>& shader);

	void apply(const DrawContext& context);
	void clear();

protected:
	virtual void applyImpl() = 0;

	const std::shared_ptr<Shader>& getShader() const { return _shader; }
};
