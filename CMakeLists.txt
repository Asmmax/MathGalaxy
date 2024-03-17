cmake_minimum_required (VERSION 3.8)

project ("MathGalaxy")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (WIN32)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} )
endif()

add_subdirectory ("deps/entt")
add_subdirectory ("deps/catch2")
add_subdirectory ("deps/glm")
add_subdirectory ("deps/infrastruct")
add_subdirectory ("deps/gl")
add_subdirectory ("deps/stb")
add_subdirectory ("deps/glfw")
add_subdirectory ("deps/imgui")
add_subdirectory ("deps/dgnix")
add_subdirectory ("Simulation")
add_subdirectory ("SimulationTests")
add_subdirectory ("GUIApp")
