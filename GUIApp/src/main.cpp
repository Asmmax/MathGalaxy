#include "Application.hpp"
#include "Window.hpp"
#include "View.hpp"
#include "gui/widgets/ViewportWidget.hpp"
#include "drawables/Transform.hpp"
#include "gui/widgets/TransformWidget.hpp"
#include "gui/widgets/WidgetGroup.hpp"
#include "gui/GUI.hpp"
#include "gui/MenuPanel.hpp"
#include "gui/menu/MenuList.hpp"
#include "gui/menu/MenuItemEnabler.hpp"
#include "Loader.hpp"
#include "RenderQueue.hpp"
#include "Material.hpp"
#include "GLFWApplicationImpl.hpp"

#include "drawables/Light.hpp"
#include "drawables/CelestialBody.hpp"
#include "drawables/CelestialSystem.hpp"
#include "drawables/Camera.hpp"
#include "drawables/Scene.hpp"

#include "ResourceManager.hpp"

#include "CameraView.hpp"
#include "MainView.hpp"
#include "RenderLoop.hpp"

#include <glm/gtx/transform.hpp>
#include <random>


std::unique_ptr<CelestialSystem> createRndSystem(ResourceManager& resManager, int materialCount, int planetPerMaterialCount)
{
	auto rndSystem = std::make_unique<CelestialSystem>();

	auto star = std::make_unique<CelestialBody>();
	star->getTransform()->setPosition(glm::vec3(0, 0, 0));

	star->setLight(std::make_unique<Light>());
	star->setMesh(resManager.getSphereMesh());
	star->setShader(resManager.getStarShader());

	Material* solarMaterial = resManager.createMaterial();
	solarMaterial->getMaterialData().setVec3(StringId("Star.BaseColor"), glm::vec3(1.0f, 0.5f, 0.0f));
	solarMaterial->getMaterialData().setVec3(StringId("Star.BoundColor"), glm::vec3(1.0f, 0.0f, 0.0f));
	solarMaterial->getMaterialData().setVec3(StringId("Star.SpaceColor"), glm::vec3(0.0f, 0.0f, 0.0f));
	star->setMaterial(solarMaterial);

	rndSystem->addBody(std::move(star));

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-100.0f, 100.0f);
	std::uniform_real_distribution<float> disColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> disScale(0.1f, 1.0f);

	std::vector<Material*> planetMaterials;

	for (int i = 0; i < materialCount; i++) {
		Material* material = resManager.createMaterial();
		material->getMaterialData().setVec3(StringId("Material.DiffuseColor"), glm::vec3(disColor(gen), disColor(gen), disColor(gen)));
		material->getMaterialData().setFloat(StringId("Material.AmbientFactor"), 0.2f);
		material->getMaterialData().setFloat(StringId("Material.DiffuseFactor"), 0.8f);
		planetMaterials.push_back(material);

		for (int j = 0; j < planetPerMaterialCount; j++) {
			auto planet = std::make_unique<CelestialBody>();

			planet->setMesh(resManager.getSphereMesh());
			planet->setShader(resManager.getPlanetShader());
			planet->setMaterial(material);

			auto bodyTransform = planet->getTransform();
			bodyTransform->setPosition(glm::vec3(dis(gen), dis(gen), dis(gen)));
			bodyTransform->setScale(glm::vec3(disScale(gen)));

			rndSystem->addBody(std::move(planet));
		}
	}

	return rndSystem;
}


std::shared_ptr<Camera> createCamera(ResourceManager& resManager)
{
	auto camera = std::make_shared<Camera>();

	camera->setSkyMesh(resManager.getSphereMesh());
	camera->setSkyShader(resManager.getSkyShader());

	Material* skyMaterial = resManager.createMaterial();
	skyMaterial->setTexture(StringId("skyMap"), resManager.getSkyTexture());
	skyMaterial->getMaterialData().setVec3(StringId("BaseColor"), glm::vec3(1.0f, 1.0f, 1.0f));
	skyMaterial->getMaterialData().setVec4(StringId("Origin"), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	camera->setSkyMaterial(skyMaterial);

	camera->getEyeTransform()->setPosition(glm::vec3{ 0, 0, 5 });

	return camera;
}


std::shared_ptr<GUI> createGUI(const std::shared_ptr<CameraView>& cameraView, const std::shared_ptr<Camera>& camera)
{
	auto viewportWidget = std::make_shared<ViewportWidget>("Main Viewport", 512, 512, cameraView->getView());

	auto cameraWidget = std::make_shared<WidgetGroup>("Camera Nodes");
	auto posWidget = std::make_shared<TransformWidget>("Eye", camera->getEyeTransform(), 200, 100);
	auto rotWidget = std::make_shared<TransformWidget>("Target", camera->getTargetTransform(), 200, 100);
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

	return gui;
}


int main()
{
	Application& app = Application::getInstance();
	app.bindImpl<GLFWApplicationImpl>();
	Window* window = app.getWindow(1280, 720, "Dear imGui Demo");
	if (!window)
		return -1;

	Loader* loader = window->getLoader();
	ResourceManager resManager;
	resManager.load(loader);

	auto scene = std::make_shared<Scene>();

	scene->setCelestialSystem(createRndSystem(resManager, 100, 100));

	std::shared_ptr<Camera> camera = createCamera(resManager);
	camera->initController(window);

	scene->setCamera(camera);

	auto cameraView = std::make_shared<CameraView>(window, camera);

	std::shared_ptr<GUI> gui = createGUI(cameraView, camera);

	auto mainView = std::make_shared<MainView>(window, gui);

	RenderLoop renderLoop{window, mainView, cameraView, scene};
	renderLoop.run();

	return 0;
}