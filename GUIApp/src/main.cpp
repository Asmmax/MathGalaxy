#include "Application.hpp"
#include "gui/DemoGUI.hpp"
#include "drawables/Triangle.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "drawables/Group.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "drawables/Sphere.hpp"
#include "CameraController.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"

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
	auto cameraWidget = std::make_shared<WidgetGroup>("Camera Nodes");
	auto posWidget = std::make_shared<TransformWidget>("Eye", cameraEye->getTransform());
	auto rotWidget = std::make_shared<TransformWidget>("Target", cameraTarget->getTransform());
	cameraWidget->addChild(posWidget);
	cameraWidget->addChild(rotWidget);

	auto menu = std::make_shared<MenuPanel>();
	
	auto windowList = std::make_shared<MenuList>("Windows");
	auto cameraWidgetEnabler = std::make_shared<MenuItemEnabler>("Camera Nodes Window", cameraWidget);

	windowList->addItem(cameraWidgetEnabler);

	menu->addList(windowList);

	auto gui = std::make_shared<GUI>();
	gui->addWidget(cameraWidget);
	gui->setMenu(menu);

	window->setGUI(std::make_shared<DemoGUI>());

	auto controller = std::make_shared<CameraController>(cameraTarget->getTransform(), cameraEye->getTransform());
	window->setController(controller);

	return window->run();
}