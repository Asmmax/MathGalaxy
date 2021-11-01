cmake_minimum_required (VERSION 3.8)

set(guiapp_include 
"include/main.h")

set(guiapp_src 
"src/main.cpp")

add_executable (GUIApp 
${guiapp_include}
${guiapp_src})

target_compile_features (GUIApp PRIVATE cxx_std_17)
target_include_directories(GUIApp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(GUIApp PRIVATE glfw PRIVATE glm_interface PRIVATE imgui PRIVATE ${OPENGL_LIBRARY})