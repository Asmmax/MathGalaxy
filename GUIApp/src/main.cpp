#include "Application.hpp"
#include "Window.hpp"
#include "gui/DemoGUI.hpp"
#include "View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "Transform.hpp"
#include "drawables/Group.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "drawables/MeshNode.hpp"
#include "meshes/Sphere.hpp"
#include "CameraController.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"
#include "impl/GLFWApplicationImpl.hpp"
#include "Material.hpp"

int main(int argc, char* argv[])
{
	Application& app = Application::getInstance();
	app.setImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	//construct drawable tree
	auto root = std::make_shared<Group>();

	auto sphereMesh = std::make_shared<Sphere>(1.0f, 10);

	auto solar = std::make_shared<MeshNode>();
	solar->setMesh(sphereMesh);
	auto solarMaterial = std::make_shared<Material>();
	solarMaterial->setMainColor(glm::vec3(1.0f, 0.5f, 0.0f));
	solar->setMaterial(solarMaterial);
	solar->getTransform()->setPosition(glm::vec3(0, 0, 0));
	root->addChild(solar);

	auto earth = std::make_shared<MeshNode>();
	earth->setMesh(sphereMesh);
	auto earthMaterial = std::make_shared<Material>();
	earthMaterial->setMainColor(glm::vec3(0.0f, 0.5f, 1.0f));
	earth->setMaterial(earthMaterial);
	earth->getTransform()->setPosition(glm::vec3(2, 0, -5));
	earth->getTransform()->setScale(glm::vec3(0.5f));
	root->addChild(earth);

	auto cameraTarget = std::make_shared<Group>();
	auto cameraEye = std::make_shared<Group>();
	cameraTarget->addChild(cameraEye);
	root->addChild(cameraTarget);
	cameraEye->getTransform()->setPosition(glm::vec3{ 0, 0, 5 });

	window->setDrawableRoot(root);
	window->setTransformRoot(root->getTransform());

	auto camera = window->creteView(512, 512, cameraEye->getTransform());

	//construct widgets
	auto viewportWidget = std::make_shared<ViewportWidget>("Main Viewport", 512,512, camera);

	auto cameraWidget = std::make_shared<WidgetGroup>("Camera Nodes");
	auto posWidget = std::make_shared<TransformWidget>("Eye", cameraEye->getTransform(), 200, 100);
	auto rotWidget = std::make_shared<TransformWidget>("Target", cameraTarget->getTransform(), 200, 100);
	cameraWidget->addChild(posWidget);
	cameraWidget->addChild(rotWidget);

	auto menu = std::make_shared<MenuPanel>();
	
	auto windowList = std::make_shared<MenuList>("Windows");
	auto cameraWidgetEnabler = std::make_shared<MenuItemEnabler>("Camera Nodes Window", cameraWidget);

	windowList->addItem(cameraWidgetEnabler);

	menu->addList(windowList);

	auto gui = std::make_shared<GUI>();
	gui->addWidget(viewportWidget);
	gui->addWidget(cameraWidget);
	gui->setMenu(menu);

	window->setGUI(gui);

	auto controller = std::make_shared<CameraController>(cameraTarget->getTransform(), cameraEye->getTransform());
	window->setController(controller);

	return window->run();
}