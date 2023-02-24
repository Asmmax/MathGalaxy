#pragma once
#include "IDrawable.hpp"
#include <memory>

class Transform;

class Node : public IDrawable
{
private:
	std::shared_ptr<Transform> _transform;

public:
	Node();

	inline std::shared_ptr<Transform> getTransform() const { return _transform; }
};
