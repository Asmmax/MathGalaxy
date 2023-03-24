#include "infrastruct/Application.hpp"
#include "infrastruct/Window.hpp"
#include "gui/DemoGUI.hpp"
#include "infrastruct/View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "drawables/Transform.hpp"
#include "infrastruct/Model.hpp"
#include "infrastruct/objects/Light.hpp"
#include "infrastruct/objects/Object.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "infrastruct/resources/Mesh.hpp"
#include "infrastruct/resources/MeshData.hpp"
#include "CameraController.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"
#include "infrastruct/impl/GLFWApplicationImpl.hpp"
#include "infrastruct/resources/Shader.hpp"
#include "Path.hpp"
#include "infrastruct/resources/Texture.hpp"
#include "infrastruct/Loader.hpp"
#include "infrastruct/resources/ShaderData.hpp"
#include "infrastruct/resources/TextureData.hpp"

#include <glm/gtx/transform.hpp>
#include <random>


int main(int argc, char* argv[])
{
	Path path("settings.dat");

	Application& app = Application::getInstance();
	app.setImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	Model model;
	Loader* loader = window->getLoader();

	auto sphereMeshData = createSphere(1.0f, 24);

	auto starVert = loadShader(path.find("shaders/star.vert"));
	auto starFrag = loadShader(path.find("shaders/star.frag"));
	auto starShader = loader->loadShader(starVert, starFrag);

	auto planetVert = loadShader(path.find("shaders/planet.vert"));
	auto planetFrag = loadShader(path.find("shaders/planet.frag"));
	auto planetShader = loader->loadShader(planetVert, planetFrag);

	auto skyVert = loadShader(path.find("shaders/sky.vert"));
	auto skyFrag = loadShader(path.find("shaders/sky.frag"));
	auto skyShader = loader->loadShader(skyVert, skyFrag);

	Mesh* sphereMesh = loader->loadMesh(sphereMeshData);

	auto skyTextureData = loadTexture(path.find("textures/sky.png"));
	Texture* skyTexture = loader->loadTexture(skyTextureData);


	//construct drawable tree
	auto root = std::make_shared<Transform>();

	auto solar = model.createObject();
	auto solarLight = model.createLight();
	auto solarTransform = std::make_shared<Transform>();
	solarTransform->setPosition(glm::vec3(0, 0, 0));
	solar->setShader(starShader);
	solar->setMesh(sphereMesh);
	auto& solarMaterial = solar->getState();
	solarMaterial.add("Star.BaseColor", glm::vec3(1.0f, 0.5f, 0.0f));
	solarMaterial.add("Star.BoundColor", glm::vec3(1.0f, 0.0f, 0.0f));
	solarMaterial.add("Star.SpaceColor", glm::vec3(0.0f, 0.0f, 0.0f));

	root->addChild(solarTransform);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-100.0, 100.0);
	std::uniform_real_distribution<> disColor(0.0, 1.0);

	std::vector<Object*> bodies;
	std::vector<std::shared_ptr<Transform>> bodyTransforms;
	for (int i = 0; i < 10000; i++) {

		auto earth = model.createObject();
		bodies.push_back(earth);
		auto earthTransform = std::make_shared<Transform>();
		bodyTransforms.push_back(earthTransform);
		earthTransform->setPosition(glm::vec3(dis(gen), dis(gen), dis(gen)));
		earthTransform->setScale(glm::vec3(0.5f));
		earth->setShader(planetShader);
		earth->setMesh(sphereMesh);
		auto& earthMaterial = earth->getState();
		earthMaterial.add("Material.DiffuseColor", glm::vec3(disColor(gen), disColor(gen), disColor(gen)));
		earthMaterial.add("Material.AmbientFactor", 0.2f);
		earthMaterial.add("Material.DiffuseFactor", 0.8f);

		root->addChild(earthTransform);

	}

	auto sky = model.createObject();
	sky->setShader(skyShader);
	sky->setMesh(sphereMesh);
	sky->addTexture("skyMap", skyTexture);
	auto& skyMaterial = sky->getState();
	skyMaterial.add("BaseColor", glm::vec3(1.0f, 1.0f, 1.0f));
	static StringId originName = StringId("Origin");
	skyMaterial.add(originName, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	auto cameraTarget = std::make_shared<Transform>();
	auto cameraEye = std::make_shared<Transform>();
	cameraTarget->addChild(cameraEye);
	root->addChild(cameraTarget);
	cameraEye->setPosition(glm::vec3{ 0, 0, 5 });

	auto camera = window->creteView(512, 512);

	auto& commonMaterial = model.getState();
	commonMaterial.add("AmbientColor", glm::vec3(0.2f, 0.1f, 0.1f));

	//construct widgets
	auto viewportWidget = std::make_shared<ViewportWidget>("Main Viewport", 512, 512, camera);

	auto cameraWidget = std::make_shared<WidgetGroup>("Camera Nodes");
	auto posWidget = std::make_shared<TransformWidget>("Eye", cameraEye, 200, 100);
	auto rotWidget = std::make_shared<TransformWidget>("Target", cameraTarget, 200, 100);
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

	auto controller = std::make_shared<CameraController>(cameraTarget, cameraEye);
	window->setController(controller);

	while (!window->isDone()) {
		window->handle();

		root->computeGlobalMatrices();

		solar->setMatrix(solarTransform->getGlobalMatrix());
		solarLight->setPosition(solarTransform->getGlobalPosition());

		for (size_t i = 0; i < bodies.size(); i++) {
			bodies[i]->setMatrix(bodyTransforms[i]->getGlobalMatrix());
		}

		sky->setMatrix(cameraEye->getGlobalMatrix() * glm::scale(glm::vec3(500.0f)));
		skyMaterial.set(originName, cameraEye->getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		auto viewMatrix = glm::inverse(cameraEye->getGlobalMatrix());
		camera->setMatrix(viewMatrix);

		camera->render(&model);

		window->render();
	}
	return 0;
}