cmake_minimum_required (VERSION 3.8)

set(guiapp_include 
"include/Application.hpp"
"include/Window.hpp"
"include/IDrawable.hpp"
"include/gui/AWidget.hpp"
"include/IController.hpp"
"include/Transform.hpp"
"include/Camera.hpp"
"include/CameraController.hpp"
"include/gui/DemoGUI.hpp"
"include/gui/widgets/TransformWidget.hpp"
"include/gui/GUI.hpp"
"include/gui/MenuPanel.hpp"
"include/gui/menu/MenuList.hpp"
"include/gui/menu/IMenuItem.hpp"
"include/gui/menu/AMenuItem.hpp"
"include/drawables/Triangle.hpp"
"include/drawables/Group.hpp"
"include/drawables/Node.hpp"
"include/drawables/Sphere.hpp"
"include/gui/IGUI.hpp"
"include/gui/menu/MenuItemEnabler.hpp"
"include/gui/widgets/WidgetGroup.hpp")

set(guiapp_src 
"src/Application.cpp"
"src/Window.cpp"
"src/main.cpp"
"src/Transform.cpp"
"src/Camera.cpp"
"src/CameraController.cpp"
"src/gui/DemoGUI.cpp"
"src/gui/widgets/TransformWidget.cpp"
"src/gui/GUI.cpp"
"src/gui/MenuPanel.cpp"
"src/gui/menu/MenuList.cpp"
"src/gui/menu/AMenuItem.cpp"
"src/drawables/Triangle.cpp"
"src/drawables/Group.cpp"
"src/drawables/Node.cpp"
"src/drawables/Sphere.cpp"
"src/gui/AWidget.cpp"
"src/gui/menu/MenuItemEnabler.cpp"
"src/gui/widgets/WidgetGroup.cpp")

add_executable (GUIApp 
${guiapp_include}
${guiapp_src} )

target_compile_features (GUIApp PRIVATE cxx_std_17)
target_include_directories(GUIApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GUIApp PRIVATE glfw PRIVATE glm_interface PRIVATE imgui PRIVATE ${OPENGL_LIBRARY})