#pragma once
#include <memory>

class Transform;
class RenderData;

class Light
{
private:
	std::shared_ptr<Transform> _transform;

public:
	Light();

	std::shared_ptr<Transform> getTransform() {return _transform;}

	void preDraw(RenderData& frameData);
};
