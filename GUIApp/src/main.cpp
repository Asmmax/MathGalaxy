#include "Application.hpp"
#include "Window.hpp"
#include "gui/DemoGUI.hpp"
#include "View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "drawables/Transform.hpp"
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
#include "RenderQueue.hpp"
#include "Material.hpp"
#include "GLFWApplicationImpl.hpp"

#include <glm/gtx/transform.hpp>
#include <random>


int main()
{
	Path path("settings.dat");

	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	Loader* loader = window->getLoader();

	auto sphereMeshData = createSphere(1.0f, 24, 48);
	Mesh* sphereMesh = loader->loadMesh(sphereMeshData);

	auto starVert = loadShader(path.find("shaders/star.vert"));
	auto starFrag = loadShader(path.find("shaders/star.frag"));
	Shader* starShader = loader->loadShader(starVert, starFrag);

	auto planetVert = loadShader(path.find("shaders/planet.vert"));
	auto planetFrag = loadShader(path.find("shaders/planet.frag"));
	Shader* planetShader = loader->loadShader(planetVert, planetFrag);

	auto skyVert = loadShader(path.find("shaders/sky.vert"));
	auto skyFrag = loadShader(path.find("shaders/sky.frag"));
	Shader* skyShader = loader->loadShader(skyVert, skyFrag);

	auto skyTextureData = readTexture(path.find("textures/sky.png"));
	Texture* skyTexture = loader->loadTexture(skyTextureData);

	auto root = std::make_shared<Transform>();
	auto solarTransform = std::make_shared<Transform>();
	solarTransform->setPosition(glm::vec3(0, 0, 0));
	root->addChild(solarTransform);

	Material* solarMaterial = loader->createMaterial();
	solarMaterial->getMaterialData().setVec3(StringId("Star.BaseColor"), glm::vec3(1.0f, 0.5f, 0.0f));
	solarMaterial->getMaterialData().setVec3(StringId("Star.BoundColor"), glm::vec3(1.0f, 0.0f, 0.0f));
	solarMaterial->getMaterialData().setVec3(StringId("Star.SpaceColor"), glm::vec3(0.0f, 0.0f, 0.0f));

	Material* skyMaterial = loader->createMaterial();
	skyMaterial->setTexture(StringId("skyMap"), skyTexture);
	skyMaterial->getMaterialData().setVec3(StringId("BaseColor"), glm::vec3(1.0f, 1.0f, 1.0f));
	skyMaterial->getMaterialData().setVec4(StringId("Origin"), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-100.0f, 100.0f);
	std::uniform_real_distribution<float> disColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> disScale(0.1f, 1.0f);

	std::vector<std::shared_ptr<Transform>> bodyTransforms;
	std::vector<Material*> bodyMaterials;

	for (int i = 0; i < 100; i++) {
		Material* material = loader->createMaterial();
		material->getMaterialData().setVec3(StringId("Material.DiffuseColor"), glm::vec3(disColor(gen), disColor(gen), disColor(gen)));
		material->getMaterialData().setFloat(StringId("Material.AmbientFactor"), 0.2f);
		material->getMaterialData().setFloat(StringId("Material.DiffuseFactor"), 0.8f);
		bodyMaterials.push_back(material);

		for (int j = 0; j < 100; j++) {
			auto bodyTransform = std::make_shared<Transform>();
			bodyTransforms.push_back(bodyTransform);
			bodyTransform->setPosition(glm::vec3(dis(gen), dis(gen), dis(gen)));
			bodyTransform->setScale(glm::vec3(disScale(gen)));
			root->addChild(bodyTransform);
		}
	}

	auto cameraTarget = std::make_shared<Transform>();
	auto cameraEye = std::make_shared<Transform>();
	cameraTarget->addChild(cameraEye);
	root->addChild(cameraTarget);
	cameraEye->setPosition(glm::vec3{ 0, 0, 5 });

	auto mainViewTex = loader->createTexture(512, 512);
	auto mainView = window->creteView(mainViewTex);
	window->setMainView(mainView);

	auto cameraTex = loader->createTexture(512, 512);
	auto camera = window->creteView(cameraTex);

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

	auto controller = std::make_shared<CameraController>(cameraTarget, cameraEye);
	window->setMouseButtonCallback([window, controller](InputEvents::MouseKey key, InputEvents::KeyState state) {
		if (key == InputEvents::MouseKey::RIGHT_BUTTON) {
			if (state == InputEvents::KeyState::KEY_DOWN) {
				window->captureMouse();
				controller->startMoving();
			}
			else if (state == InputEvents::KeyState::KEY_UP) {
				window->uncaptureMouse();
				controller->stopMoving();
			}
		}
		});
	window->setMouseMoveCallback([controller](double posX, double posY) {
		controller->moveMouse(posX, posY);
		});
	window->setMouseScrollCallback([controller](double step) {
		controller->scrollMouse(step);
		});

	RenderData frameData;
	RenderQueue renderQueue;

	bool imguiInited = false;

	while (!window->isDone()) {
		window->handle();

		root->computeGlobalMatrices();

		frameData.clear();
		frameData.setVec3(StringId("AmbientColor"), glm::vec3(0.2f, 0.1f, 0.1f));
		frameData.setInt(StringId("PointLightCount"), 1);
		frameData.setVec3(StringId("PointLights[0].Position"), solarTransform->getGlobalPosition());
		frameData.setVec3(StringId("PointLights[0].Color"), glm::vec3(1.0f, 1.0f, 1.0f));
		frameData.setFloat(StringId("PointLights[0].Intensity"), 1.0f);
		frameData.setFloat(StringId("PointLights[0].Radius"), 100.0f);
		frameData.setFloat(StringId("PointLights[0].FadingArea"), 0.0f);

		renderQueue.clear();

		RenderCommand solarCmd;
		solarCmd.shader = starShader;
		solarCmd.material = solarMaterial;
		solarCmd.mesh = sphereMesh;
		solarCmd.modelMatrix = solarTransform->getGlobalMatrix();
		renderQueue.submit(solarCmd);

		for (size_t i = 0; i < bodyTransforms.size(); i++) {
			RenderCommand cmd;
			cmd.shader = planetShader;
			cmd.material = bodyMaterials[i / 100];
			cmd.mesh = sphereMesh;
			cmd.modelMatrix = bodyTransforms[i]->getGlobalMatrix();
			renderQueue.submit(cmd);
		}

		RenderCommand skyCmd;
		skyCmd.shader = skyShader;
		skyCmd.material = skyMaterial;
		skyCmd.mesh = sphereMesh;
		skyCmd.modelMatrix = cameraEye->getGlobalMatrix() * glm::scale(glm::vec3(500.0f));
		skyMaterial->getMaterialData().setVec4(StringId("Origin"), cameraEye->getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		renderQueue.submit(skyCmd);

		renderQueue.sort();

		const auto viewMatrix = glm::inverse(cameraEye->getGlobalMatrix());

		camera->beginRender();
		camera->render(renderQueue, frameData, viewMatrix);
		camera->endRender();

		int frameWidth = 0;
		int frameHeight = 0;
		window->getFrameSize(frameWidth, frameHeight);
		mainView->setSize(frameWidth, frameHeight);

		mainView->beginRender();
		if (!imguiInited) {
			gui->init();
			imguiInited = true;
		}
		mainView->setupImgui();
		gui->setup();
		mainView->renderImgui();
		mainView->endRender();

		window->render();
		window->swapBuffers();
	}

	loader->release(sphereMesh);
	loader->release(skyTexture);
	loader->release(starShader);
	loader->release(planetShader);
	loader->release(skyShader);
	loader->release(solarMaterial);
	loader->release(skyMaterial);
	for (Material* mat : bodyMaterials) {
		loader->release(mat);
	}
	loader->release(mainViewTex);
	loader->release(cameraTex);

	return 0;
}