#pragma once
#include "glm/glm.hpp"
#include <memory>
#include <vector>

class Transform
{
private:
	glm::vec3 _localPosition;
	glm::vec3 _localRotation;
	glm::vec3 _localScale;
	std::vector<std::shared_ptr<Transform>> _children;
	mutable glm::mat4 _localMatrix;
	mutable glm::mat4 _globalMatrix;
	mutable bool _dirtyLocalMatrix;
public:
	Transform(const glm::vec3& localPosition = glm::vec3(0.0f),
		const glm::vec3& localRotation = glm::vec3(0.0),
		const glm::vec3& localScale = glm::vec3(1.0f));

	void setPosition(const glm::vec3& localPosition);
	void setRotation(const glm::vec3& localRotation);
	void setScale(const glm::vec3& localScale);

	const glm::vec3& getLocalPosition() const { return _localPosition; }
	const glm::vec3& getLocalRotation() const { return _localRotation; }
	const glm::vec3& getLocalScale() const { return _localScale; }

	glm::vec3 getGlobalPosition() const;

	void addChild(const std::shared_ptr<Transform>& child);

	const glm::mat4& getLocalMatrix() const;
	const glm::mat4& getGlobalMatrix() const { return _globalMatrix; }
	void computeGlobalMatrices(const glm::mat4& matrix = glm::mat4(1.0f));
protected:
	void computeLocalMatrix() const;
};
