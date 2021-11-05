#include "Application.hpp"
#include "widgets/DemoWidget.hpp"
#include "drawables/Triangle.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "drawables/Group.hpp"
#include "widgets/TransformWidget.hpp"
#include "widgets/WidgetSet.hpp"
#include "drawables/Sphere.hpp"

int main(int argc, char* argv[])
{
	Application& app = Application::getInstance();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	//construct drawable tree
	auto root = std::make_shared<Group>();
	auto solar = std::make_shared<Sphere>(1.0f, 20, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
	solar->getTransform()->setPosition(glm::vec3(0, 0, 0));
	root->addChild(solar);

	auto earth = std::make_shared<Sphere>(0.5f, 10, glm::vec4(0.0f, 0.5f, 1.0f, 1.0f));
	earth->getTransform()->setPosition(glm::vec3(2, 0, -5));
	root->addChild(earth);

	auto cameraTarget = std::make_shared<Group>();
	auto cameraEye = std::make_shared<Group>();
	cameraTarget->addChild(cameraEye);
	root->addChild(cameraTarget);
	cameraEye->getTransform()->setPosition(glm::vec3{ 0, 0, 5 });

	window->setDrawableRoot(root);
	window->setTransformRoot(root->getTransform());

	auto camera = std::make_shared<Camera>(cameraEye->getTransform());
	window->setCamera(camera);

	//construct widgets
	auto posWidget = std::make_shared<TransformWidget>("Eye", cameraEye->getTransform());
	auto rotWidget = std::make_shared<TransformWidget>("Target", cameraTarget->getTransform());

	auto groupWidget = std::make_shared<WidgetSet>();
	groupWidget->addChild(posWidget);
	groupWidget->addChild(rotWidget);

	window->setWidgetRoot(groupWidget);

	return window->run();
}