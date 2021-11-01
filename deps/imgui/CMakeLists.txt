cmake_minimum_required (VERSION 3.8)

set(imgui_include 
"imgui/imconfig.h"
"imgui/imgui.h"
"imgui/imgui_internal.h"
"imgui/imstb_rectpack.h"
"imgui/imstb_textedit.h"
"imgui/imstb_truetype.h"
"imgui/backends/imgui_impl_glfw.h"
"imgui/backends/imgui_impl_opengl3.h"
"imgui/backends/imgui_impl_opengl3_loader.h")

set(imgui_src 
"imgui/imgui.cpp"
"imgui/imgui_demo.cpp"
"imgui/imgui_draw.cpp"
"imgui/imgui_tables.cpp"
"imgui/imgui_widgets.cpp"
"imgui/backends/imgui_impl_glfw.cpp"
"imgui/backends/imgui_impl_opengl3.cpp")

add_library (imgui STATIC 
${imgui_include}  
${imgui_src})

target_compile_features (imgui PRIVATE cxx_std_11)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui/")
target_link_libraries(imgui PRIVATE glfw PRIVATE ${OPENGL_LIBRARY} PRIVATE ${CMAKE_DL_LIBS})
