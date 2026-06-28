#pragma once
#include <memory>
#include <vector>

class Transform;
class CelestialBody;
class RenderData;
class RenderQueue;

class CelestialSystem
{
private:
	std::shared_ptr<Transform> _transform;
	std::vector<std::unique_ptr<CelestialBody>> _bodies;
	
public:
	CelestialSystem();
	~CelestialSystem();

	void addBody(std::unique_ptr<CelestialBody> body);

	std::shared_ptr<Transform> getTransform() {return _transform;}

	void preDraw(RenderData& frameData);

	void draw(RenderQueue& renderQueue);
};
