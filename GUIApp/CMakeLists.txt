cmake_minimum_required (VERSION 3.8)

set(guiapp_include 
"include/Application.hpp"
"include/Window.hpp"
"include/IDrawable.hpp"
"include/IWidget.hpp"
"include/IController.hpp"
"include/Transform.hpp"
"include/Camera.hpp"
"include/CameraController.hpp"
"include/widgets/DemoWidget.hpp"
"include/widgets/TransformWidget.hpp"
"include/widgets/WidgetSet.hpp"
"include/drawables/Triangle.hpp"
"include/drawables/Group.hpp"
"include/drawables/Node.hpp"
"include/drawables/Sphere.hpp")

set(guiapp_src 
"src/Application.cpp"
"src/Window.cpp"
"src/main.cpp"
"src/Transform.cpp"
"src/Camera.cpp"
"src/CameraController.cpp"
"src/widgets/DemoWidget.cpp"
"src/widgets/TransformWidget.cpp"
"src/widgets/WidgetSet.cpp"
"src/drawables/Triangle.cpp"
"src/drawables/Group.cpp"
"src/drawables/Node.cpp"
"src/drawables/Sphere.cpp")

add_executable (GUIApp 
${guiapp_include}
${guiapp_src})

target_compile_features (GUIApp PRIVATE cxx_std_17)
target_include_directories(GUIApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GUIApp PRIVATE glfw PRIVATE glm_interface PRIVATE imgui PRIVATE ${OPENGL_LIBRARY})