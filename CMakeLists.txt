cmake_minimum_required (VERSION 3.8)

project ("MathGalaxy")

if (WIN32)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
endif()

set(BUILD_SHARED_LIBS on)
set(GLFW_BUILD_DOCS off)
set(GLFW_BUILD_EXAMPLES off)
set(GLFW_BUILD_TESTS off)

if (WIN32)
set( GLFW_BUILD_WIN32 on )
set( USE_MSVC_RUNTIME_LIBRARY_DLL on )
else()
set( GLFW_BUILD_WIN32 off )
set( USE_MSVC_RUNTIME_LIBRARY_DLL off )
endif()

find_package(OpenGL REQUIRED)

add_subdirectory ("deps/entt")
add_subdirectory ("deps/catch2")
add_subdirectory ("deps/glfw")
add_subdirectory ("deps/glm")
add_subdirectory ("deps/imgui")
add_subdirectory ("Simulation")
add_subdirectory ("SimulationTests")
add_subdirectory ("GUIApp")
