cmake_minimum_required (VERSION 3.8)

set(glfw_include_dir "include/")
set(glfw_libs_dir "libs/")

find_library(FREE_IMAGE_LIBRARY 
			NAMES glfw3
			PATHS "${CMAKE_CURRENT_SOURCE_DIR}/${glfw_libs_dir}" 
			NO_DEFAULT_PATH
)

add_library (glfw_interface INTERFACE)

target_include_directories(glfw_interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/${glfw_include_dir}")
target_link_libraries(glfw_interface INTERFACE ${FREE_IMAGE_LIBRARY})
