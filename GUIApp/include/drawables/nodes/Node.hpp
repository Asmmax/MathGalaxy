#pragma once
#include "infrastruct/IDrawable.hpp"
#include <memory>

class Transform;
class Group;

class Node : public IDrawable, public std::enable_shared_from_this<Node>
{
private:
	std::shared_ptr<Transform> _transform;
	std::weak_ptr<Group> _parent;

public:
	Node();

	virtual void deinit() = 0;
	void setParent(const std::weak_ptr<Group>& parent);
	inline std::shared_ptr<Transform> getTransform() const { return _transform; }
};
