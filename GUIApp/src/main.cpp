#include "Application.hpp"
#include "Window.hpp"
#include "gui/DemoGUI.hpp"
#include "View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "drawables/Transform.hpp"
#include "Model.hpp"
#include "objects/Light.hpp"
#include "objects/Object.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "resources/Mesh.hpp"
#include "resources/MeshData.hpp"
#include "CameraController.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"
#include "resources/Shader.hpp"
#include "Path.hpp"
#include "resources/Texture.hpp"
#include "Loader.hpp"
#include "resources/ShaderData.hpp"
#include "resources/TextureData.hpp"
#include "objects/Batch.hpp"

#include <glm/gtx/transform.hpp>
#include <random>


int main(int argc, char* argv[])
{
	Path path("settings.dat");

	Application& app = Application::getInstance();
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

	auto solarBatch = model.createBatch();
	auto solar = solarBatch->createObject();
	auto solarLight = model.createLight();
	auto solarTransform = std::make_shared<Transform>();
	solarTransform->setPosition(glm::vec3(0, 0, 0));
	solarBatch->setShader(starShader);
	solar->setMesh(sphereMesh);
	auto& solarMaterial = solarBatch->getState();
	solarMaterial.add(StringId("Star.BaseColor"), glm::vec3(1.0f, 0.5f, 0.0f));
	solarMaterial.add(StringId("Star.BoundColor"), glm::vec3(1.0f, 0.0f, 0.0f));
	solarMaterial.add(StringId("Star.SpaceColor"), glm::vec3(0.0f, 0.0f, 0.0f));

	root->addChild(solarTransform);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-100.0f, 100.0f);
	std::uniform_real_distribution<float> disColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> disScale(0.1f, 1.0f);

	std::vector<Object*> bodies;
	std::vector<std::shared_ptr<Transform>> bodyTransforms;
	for (int i = 0; i < 100; i++) {

		auto earthBatch = model.createBatch();
		earthBatch->setShader(planetShader);
		auto& earthMaterial = earthBatch->getState();
		earthMaterial.add(StringId("Material.DiffuseColor"), glm::vec3(disColor(gen), disColor(gen), disColor(gen)));
		earthMaterial.add(StringId("Material.AmbientFactor"), 0.2f);
		earthMaterial.add(StringId("Material.DiffuseFactor"), 0.8f);

		for (int j = 0; j < 100; j++) {

			auto earth = earthBatch->createObject();
			bodies.push_back(earth);
			auto earthTransform = std::make_shared<Transform>();
			bodyTransforms.push_back(earthTransform);
			earthTransform->setPosition(glm::vec3(dis(gen), dis(gen), dis(gen)));
			earthTransform->setScale(glm::vec3(disScale(gen)));
			earth->setMesh(sphereMesh);

			root->addChild(earthTransform);
		}
	}

	auto skyBatch = model.createBatch();
	auto sky = skyBatch->createObject();
	skyBatch->setShader(skyShader);
	sky->setMesh(sphereMesh);
	skyBatch->addTexture(StringId("skyMap"), skyTexture);
	auto& skyMaterial = skyBatch->getState();
	skyMaterial.add(StringId("BaseColor"), glm::vec3(1.0f, 1.0f, 1.0f));
	static StringId originName = StringId("Origin");
	skyMaterial.add(originName, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	auto cameraTarget = std::make_shared<Transform>();
	auto cameraEye = std::make_shared<Transform>();
	cameraTarget->addChild(cameraEye);
	root->addChild(cameraTarget);
	cameraEye->setPosition(glm::vec3{ 0, 0, 5 });

	auto camera = window->creteView(512, 512);

	auto& commonMaterial = model.getState();
	commonMaterial.add(StringId("AmbientColor"), glm::vec3(0.2f, 0.1f, 0.1f));

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
	window->setResetMousePosCallback([controller](double posX, double posY) {
		controller->resetMousePos(posX, posY);
		});
	window->setMoveMouseCallback([controller](double posX, double posY) {
		controller->moveMouse(posX, posY);
		});
	window->setScrollMouseCallback([controller](double step) {
		controller->scrollMouse(step);
		});

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