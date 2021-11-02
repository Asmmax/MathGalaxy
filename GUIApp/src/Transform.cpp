#include "Transform.hpp"
#include "glm/gtx/transform.hpp"

Transform::Transform(const glm::vec3& localPosition,
	const glm::vec3& localRotation,
	const glm::vec3& localScale) :
	_localPosition(localPosition),
	_localRotation(localRotation),
	_localScale(localScale),
	_localMatrix(),
	_globalMatrix(),
	_dirtyLocalMatrix(true)
{
}

void Transform::setPosition(const glm::vec3& localPosition)
{
	_localPosition = localPosition;
	_dirtyLocalMatrix = true;
}

void Transform::setRotation(const glm::vec3& localRotation)
{
	_localRotation = localRotation;
	_dirtyLocalMatrix = true;
}

void Transform::setScale(const glm::vec3& localScale)
{
	_localScale = localScale;
	_dirtyLocalMatrix = true;
}

void Transform::addChild(const std::shared_ptr<Transform>& child)
{
	_children.emplace_back(child);
}

const glm::mat4& Transform::getLocalMatrix() const
{
	if (_dirtyLocalMatrix) {
		computeLocalMatrix();
	}
	return _localMatrix;
}

void Transform::computeGlobalMatrices(const glm::mat4& matrix)
{
	auto& localMatrix = getLocalMatrix();
	_globalMatrix = matrix * localMatrix;
	for (auto child : _children)
	{
		child->computeGlobalMatrices(_globalMatrix);
	}
}

void Transform::computeLocalMatrix() const
{
	glm::mat4 rotationMatrix = glm::rotate(_localRotation.z, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(_localRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(_localRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	_localMatrix = glm::translate(_localPosition) * rotationMatrix * glm::scale(_localScale);
	_dirtyLocalMatrix = false;
}
