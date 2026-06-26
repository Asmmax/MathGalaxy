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


class ResourceManager
{
private:
	Mesh* _sphereMesh{};
	Shader* _starShader{};
	Shader* _planetShader{};
	Shader* _skyShader{};
	Texture* _skyTexture{};
	Loader* _loader{};
	std::vector<Material*> _materials;

public:
	~ResourceManager()
	{
		if (_loader){
			_loader->release(_sphereMesh);
			_loader->release(_skyTexture);
			_loader->release(_starShader);
			_loader->release(_planetShader);
			_loader->release(_skyShader);
		}
	}

	void load(Loader* loader)
	{
		_loader = loader;

		Path path("settings.dat");

		auto sphereMeshData = createSphere(1.0f, 24, 48);
		_sphereMesh = loader->loadMesh(sphereMeshData);

		auto starVert = loadShader(path.find("shaders/star.vert"));
		auto starFrag = loadShader(path.find("shaders/star.frag"));
		_starShader = loader->loadShader(starVert, starFrag);

		auto planetVert = loadShader(path.find("shaders/planet.vert"));
		auto planetFrag = loadShader(path.find("shaders/planet.frag"));
		_planetShader = loader->loadShader(planetVert, planetFrag);

		auto skyVert = loadShader(path.find("shaders/sky.vert"));
		auto skyFrag = loadShader(path.find("shaders/sky.frag"));
		_skyShader = loader->loadShader(skyVert, skyFrag);

		auto skyTextureData = readTexture(path.find("textures/sky.png"));
		_skyTexture = loader->loadTexture(skyTextureData);
	}

	Mesh* getSphereMesh() const {return _sphereMesh;}
	Shader* getStarShader() const {return _starShader;}
	Shader* getPlanetShader() const {return _planetShader;}
	Shader* getSkyShader() const {return _skyShader;}
	Texture* getSkyTexture() const {return _skyTexture;}

	Material* createMaterial()
	{
		if (!_loader)
		{
			return nullptr;
		}

		Material* newMaterial = _loader->createMaterial();
		_materials.push_back(newMaterial);
		return newMaterial;
	}
	Material* getMaterial(int idx) const {return _materials[idx];}
	int getMaterialCount() const {return static_cast<int>(_materials.size());}
};


class Light
{
private:
	std::shared_ptr<Transform> _transform;

public:
	Light()
	{
		_transform = std::make_shared<Transform>();
	}

	std::shared_ptr<Transform> getTransform() {return _transform;}

	void preDraw(RenderData& frameData)
	{
		frameData.setInt(StringId("PointLightCount"), 1);
		frameData.setVec3(StringId("PointLights[0].Position"), _transform->getGlobalPosition());
		frameData.setVec3(StringId("PointLights[0].Color"), glm::vec3(1.0f, 1.0f, 1.0f));
		frameData.setFloat(StringId("PointLights[0].Intensity"), 1.0f);
		frameData.setFloat(StringId("PointLights[0].Radius"), 100.0f);
		frameData.setFloat(StringId("PointLights[0].FadingArea"), 0.0f);
	}
};


class CelestialBody
{
private:
	Shader* _shader{};
	Material* _material{};
	Mesh* _mesh{};
	std::shared_ptr<Transform> _transform;
	std::unique_ptr<Light> _light;

public:
	CelestialBody()
	{
		_transform = std::make_shared<Transform>();
	}

	void setShader(Shader* shader) {_shader = shader;}
	void setMaterial(Material* material) {_material = material;}
	void setMesh(Mesh* mesh) {_mesh = mesh;}
	void setLight(std::unique_ptr<Light> light)
	{
		_transform->addChild(light->getTransform());
		_light = std::move(light);
	}

	std::shared_ptr<Transform> getTransform() {return _transform;}
	Material* getMaterial() {return _material;}

	void preDraw(RenderData& frameData)
	{
		if (_light)
		{
			_light->preDraw(frameData);
		}
	}

	void draw(RenderQueue& renderQueue)
	{
		RenderCommand solarCmd;
		solarCmd.shader = _shader;
		solarCmd.material = _material;
		solarCmd.mesh = _mesh;
		solarCmd.modelMatrix = _transform->getGlobalMatrix();
		renderQueue.submit(solarCmd);
	}
};


class CelestialSystem
{
private:
	std::shared_ptr<Transform> _transform;
	std::vector<std::unique_ptr<CelestialBody>> _bodies;
	
public:
	CelestialSystem()
	{
		_transform = std::make_shared<Transform>();
	}

	void addBody(std::unique_ptr<CelestialBody> body)
	{
		_transform->addChild(body->getTransform());
		_bodies.push_back(std::move(body));
	}

	std::shared_ptr<Transform> getTransform() {return _transform;}

	void preDraw(RenderData& frameData)
	{
		for (auto& body : _bodies) {
			body->preDraw(frameData);
		}
	}

	void draw(RenderQueue& renderQueue)
	{
		for (auto& body : _bodies) {
			body->draw(renderQueue);
		}
	}
};


class Camera
{
private:
	Shader* _skyShader{};
	Material* _skyMaterial{};
	Mesh* _skyMesh{};
	std::shared_ptr<Transform> _cameraTarget;
	std::shared_ptr<Transform> _cameraEye;
	std::shared_ptr<CameraController> _controller;
public:
	Camera()
	{
		_cameraTarget = std::make_shared<Transform>();
		_cameraEye = std::make_shared<Transform>();
		_cameraTarget->addChild(_cameraEye);
	}

	void initController(Window* window)
	{
		_controller = std::make_shared<CameraController>(_cameraTarget, _cameraEye);
		window->setMouseButtonCallback([window, controller = _controller](InputEvents::MouseKey key, InputEvents::KeyState state) {
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
		window->setMouseMoveCallback([controller = _controller](double posX, double posY) {
			controller->moveMouse(posX, posY);
			});
		window->setMouseScrollCallback([controller = _controller](double step) {
			controller->scrollMouse(step);
			});
	}

	void setSkyShader(Shader* skyShader) {_skyShader = skyShader;}
	void setSkyMaterial(Material* skyMaterial) {_skyMaterial = skyMaterial;}
	void setSkyMesh(Mesh* skyMesh) {_skyMesh = skyMesh;}

	std::shared_ptr<Transform> getTargetTransform() {return _cameraTarget;}
	std::shared_ptr<Transform> getEyeTransform() {return _cameraEye;}

	void draw(RenderQueue& renderQueue)
	{
		RenderCommand skyCmd;
		skyCmd.shader = _skyShader;
		skyCmd.material = _skyMaterial;
		skyCmd.mesh = _skyMesh;
		skyCmd.modelMatrix = _cameraEye->getGlobalMatrix() * glm::scale(glm::vec3(500.0f));
		_skyMaterial->getMaterialData().setVec4(StringId("Origin"), _cameraEye->getGlobalMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		renderQueue.submit(skyCmd);
	}
};


class Scene
{
private:
	std::unique_ptr<CelestialSystem> _celSystem;
	std::shared_ptr<Camera> _camera;
	std::shared_ptr<Transform> _root;

public:
	Scene()
	{
		_root = std::make_shared<Transform>();
	}

	void setCelestialSystem(std::unique_ptr<CelestialSystem> celSystem)
	{
		_root->addChild(celSystem->getTransform());
		_celSystem = std::move(celSystem);
	}

	void setCamera(const std::shared_ptr<Camera>& camera)
	{
		_root->addChild(camera->getTargetTransform());
		_camera = camera;
	}

	std::shared_ptr<Transform> getRoot() {return _root;}

	void draw(RenderQueue& renderQueue, RenderData& frameData)
	{
		_root->computeGlobalMatrices();
		frameData.setVec3(StringId("AmbientColor"), glm::vec3(0.2f, 0.1f, 0.1f));

		_celSystem->preDraw(frameData);

		_celSystem->draw(renderQueue);
		_camera->draw(renderQueue);
	}
};


class CameraView
{
private:
	Texture* _cameraTex{};
	View* _cameraView{};
	Loader* _loader{};
	std::shared_ptr<Camera> _cameraObj;

public:
	CameraView(Window* window, const std::shared_ptr<Camera>& cameraObj):
		_cameraObj(cameraObj)
	{
		_loader = window->getLoader();
		_cameraTex = _loader->createTexture(512, 512);
		_cameraView = window->creteView(_cameraTex);
	}

	~CameraView()
	{
		if (_loader)
		{
			_loader->release(_cameraTex);
		}
	}

	View* getView() { return _cameraView; }

	void render(const RenderQueue& renderQueue, const RenderData& frameData)
	{
		const auto viewMatrix = glm::inverse(_cameraObj->getEyeTransform()->getGlobalMatrix());

		_cameraView->beginRender();
		_cameraView->render(renderQueue, frameData, viewMatrix);
		_cameraView->endRender();
	}
};


class MainView
{
private:
	Texture* _mainViewTex{};
	View* _mainView{};
	Window* _window{};
	std::shared_ptr<GUI> _gui;
	bool _imguiInited{false};
public:
	MainView(Window* window, const std::shared_ptr<GUI>& gui):
		_window(window),
		_gui(gui)
	{
		Loader* loader = _window->getLoader();
		_mainViewTex = loader->createTexture(512, 512);
		_mainView = window->creteView(_mainViewTex);
		window->setMainView(_mainView);
	}

	~MainView()
	{
		if (_window)
		{
			Loader* loader = _window->getLoader();
			loader->release(_mainViewTex);
		}
	}

	void render()
	{
		int frameWidth = 0;
		int frameHeight = 0;
		_window->getFrameSize(frameWidth, frameHeight);
		_mainView->setSize(frameWidth, frameHeight);

		_mainView->beginRender();
		if (!_imguiInited) {
			_gui->init();
			_imguiInited = true;
		}
		_mainView->setupImgui();
		_gui->setup();
		_mainView->renderImgui();
		_mainView->endRender();
	}
};


class RenderLoop
{
private:
	std::shared_ptr<Scene> _scene;
	std::shared_ptr<CameraView> _cameraView;
	std::shared_ptr<MainView> _mainView;
	Window* _window{};

public:
	RenderLoop(Window* window, const std::shared_ptr<MainView>& mainView, const std::shared_ptr<CameraView>& cameraView, const std::shared_ptr<Scene>& scene):
		_window(window),
		_mainView(mainView),
		_cameraView(cameraView),
		_scene(scene)
	{
	}

	void run()
	{
		RenderData frameData;
		RenderQueue renderQueue;

		while (!_window->isDone()) {
			_window->handle();

			renderQueue.clear();
			frameData.clear();

			_scene->draw(renderQueue, frameData);

			renderQueue.sort();

			_cameraView->render(renderQueue, frameData);
			_mainView->render();

			_window->render();
			_window->swapBuffers();
		}
	}
};


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