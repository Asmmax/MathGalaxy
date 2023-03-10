#include "infrastruct/Application.hpp"
#include "infrastruct/Window.hpp"
#include "gui/DemoGUI.hpp"
#include "infrastruct/View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "drawables/Transform.hpp"
#include "drawables/nodes/Group.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "drawables/nodes/MeshNode.hpp"
#include "infrastruct/resources/meshes/Sphere.hpp"
#include "CameraController.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"
#include "infrastruct/impl/GLFWApplicationImpl.hpp"
#include "drawables/materials/DiffusedMaterial.hpp"
#include "drawables/materials/StarMaterial.hpp"
#include "infrastruct/resources/Shader.hpp"
#include "Path.hpp"
#include "drawables/nodes/Light.hpp"
#include "drawables/Sky.hpp"
#include "drawables/materials/SkyMaterial.hpp"
#include "infrastruct/resources/Texture.hpp"

int main(int argc, char* argv[])
{
	Path path("settings.dat");

	Application& app = Application::getInstance();
	app.setImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	//construct drawable tree
	auto root = std::make_shared<Group>();

	auto planetShader = std::make_shared<Shader>();
	planetShader->loadVertexShader(path.find("shaders/planet.vert"));
	planetShader->loadFragmentShader(path.find("shaders/planet.frag"));

	auto starShader = std::make_shared<Shader>();
	starShader->loadVertexShader(path.find("shaders/star.vert"));
	starShader->loadFragmentShader(path.find("shaders/star.frag"));

	auto skyShader = std::make_shared<Shader>();
	skyShader->loadVertexShader(path.find("shaders/sky.vert"));
	skyShader->loadFragmentShader(path.find("shaders/sky.frag"));

	auto skyTexture = std::make_shared<Texture>(path.find("textures/sky.png"));

	auto sphereMesh = std::make_shared<Sphere>(1.0f, 24);

	auto solarGroup = std::make_shared<Group>();
	solarGroup->getTransform()->setPosition(glm::vec3(0, 0, 0));
	auto solar = std::make_shared<MeshNode>();
	solar->setMesh(sphereMesh);
	auto solarMaterial = std::make_shared<StarMaterial>(starShader);
	solarMaterial->setBaseColor(glm::vec3(1.0f, 0.5f, 0.0f));
	solarMaterial->setBoundColor(glm::vec3(1.0f, 0.0f, 0.0f));
	solar->setMaterial(solarMaterial);
	solarGroup->attachChild(solar);
	auto solarLight = std::make_shared<Light>();
	solarGroup->attachChild(solarLight);
	root->attachChild(solarGroup);

	auto earthGroup = std::make_shared<Group>();
	earthGroup->getTransform()->setPosition(glm::vec3(2, 0, -5));
	earthGroup->getTransform()->setScale(glm::vec3(0.5f));
	auto earth = std::make_shared<MeshNode>();
	earth->setMesh(sphereMesh);
	auto earthMaterial = std::make_shared<DiffusedMaterial>(planetShader);
	earthMaterial->setDiffuseColor(glm::vec3(0.0f, 0.5f, 1.0f));
	earth->setMaterial(earthMaterial);
	earthGroup->attachChild(earth);
	root->attachChild(earthGroup);

	auto cameraTarget = std::make_shared<Group>();
	auto cameraEye = std::make_shared<Group>();
	cameraTarget->attachChild(cameraEye);
	root->attachChild(cameraTarget);
	cameraEye->getTransform()->setPosition(glm::vec3{ 0, 0, 5 });

	window->setDrawableRoot(root);

	auto camera = window->creteView(512, 512);

	auto cameraShared = camera.lock();
	auto sky = std::make_shared<Sky>(sphereMesh, skyShader);
	sky->setAmbientColor(glm::vec3(0.2f, 0.1f, 0.1f));
	sky->setBaseTexture(skyTexture);
	cameraShared->setSky(sky);

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

	cameraTarget->setParent(solarGroup);


	auto&& rootTransform = root->getTransform();

	while (!window->isDone()) {
		window->handle();

		rootTransform->computeGlobalMatrices();

		auto viewMatrix = glm::inverse(cameraEye->getTransform()->getGlobalMatrix());
		cameraShared->setMatrix(viewMatrix);

		window->render();
		window->renderGUI();
	}
	return 0;
}