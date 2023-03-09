#include "Transform.hpp"
#include "glm/gtx/transform.hpp"
#include <cmath>

const float pi = 3.1415926536f;

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
	_localRotation.x = fmod(localRotation.x + 360.0f, 360.0f);
	_localRotation.y = fmod(localRotation.y + 360.0f, 360.0f);
	_localRotation.z = fmod(localRotation.z + 360.0f, 360.0f);

	_dirtyLocalMatrix = true;
}

void Transform::setScale(const glm::vec3& localScale)
{
	_localScale = localScale;
	_dirtyLocalMatrix = true;
}

glm::vec3 Transform::getGlobalPosition() const
{
	return getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Transform::addChild(const std::shared_ptr<Transform>& child)
{
	_children.emplace_back(child);
}

void Transform::removeChild(const std::shared_ptr<Transform>& child)
{
	auto lastIt = std::remove(_children.begin(), _children.end(), child);
	_children.erase(lastIt, _children.end());
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
	glm::mat4 rotationMatrix = 
		glm::rotate(_localRotation.z / 180 * pi, glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(_localRotation.y / 180 * pi, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(_localRotation.x / 180 * pi, glm::vec3(1.0f, 0.0f, 0.0f));
	_localMatrix = glm::translate(_localPosition) * rotationMatrix * glm::scale(_localScale);
	_dirtyLocalMatrix = false;
}
