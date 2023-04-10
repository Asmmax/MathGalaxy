#pragma once
#include "CommonMath.hpp"
#include <array>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct BBox
{
	float xMin = std::numeric_limits<float>::max();
	float yMin = std::numeric_limits<float>::max();
	float zMin = std::numeric_limits<float>::max();
	float xMax = std::numeric_limits<float>::lowest();
	float yMax = std::numeric_limits<float>::lowest();
	float zMax = std::numeric_limits<float>::lowest();

	inline void addPoint(float x, float y, float z);
	inline void addPoint(const glm::vec3& point);
	inline BBox project(const glm::mat4& projMatrix) const;
	inline bool isOverlapped(const BBox& other, float epsilon = std::numeric_limits<float>::epsilon()) const;
};




void BBox::addPoint(float x, float y, float z)
{
	xMin = MIN(x, xMin);
	yMin = MIN(y, yMin);
	zMin = MIN(z, zMin);

	xMax = MAX(x, xMax);
	yMax = MAX(y, yMax);
	zMax = MAX(z, zMax);
}

void BBox::addPoint(const glm::vec3& point)
{
	xMin = MIN(point.x, xMin);
	yMin = MIN(point.y, yMin);
	zMin = MIN(point.z, zMin);

	xMax = MAX(point.x, xMax);
	yMax = MAX(point.y, yMax);
	zMax = MAX(point.z, zMax);
}

BBox BBox::project(const glm::mat4& projMatrix) const
{
	std::array<glm::vec4, 8> vertices = {
		glm::vec4{xMin, yMin, zMin, 1.0f},
		glm::vec4{xMin, yMin, zMax, 1.0f},
		glm::vec4{xMin, yMax, zMin, 1.0f},
		glm::vec4{xMin, yMax, zMax, 1.0f},
		glm::vec4{xMax, yMin, zMin, 1.0f},
		glm::vec4{xMax, yMin, zMax, 1.0f},
		glm::vec4{xMax, yMax, zMin, 1.0f},
		glm::vec4{xMax, yMax, zMax, 1.0f}
	};

	std::array<glm::vec4, 8> projectedVertices;
	for (int i = 0; i < 8; i++) {
		projectedVertices[i] = projMatrix * vertices[i];
	}

	BBox projectedBounds;
	for (auto& projectedVertex : projectedVertices) {
		projectedBounds.addPoint(projectedVertex.x / projectedVertex.w, projectedVertex.y / projectedVertex.w, projectedVertex.z / projectedVertex.w);
	}

	return projectedBounds;
}

bool BBox::isOverlapped(const BBox& other, float epsilon) const
{
	return !(FLOAT_IS_GREATER(xMin, other.xMax, epsilon)
		|| FLOAT_IS_LESS(xMax, other.xMin, epsilon)
		|| FLOAT_IS_GREATER(yMin, other.yMax, epsilon)
		|| FLOAT_IS_LESS(yMax, other.yMin, epsilon)
		|| FLOAT_IS_GREATER(zMin, other.zMax, epsilon)
		|| FLOAT_IS_LESS(zMax, other.zMin, epsilon));
}
