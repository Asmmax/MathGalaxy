cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(simulations_private_include 
"include/private/World.hpp")

set(simulations_public_include 
"include/public/IWorld.hpp"
"include/public/Simulation.hpp"
"include/public/components/Position.hpp"
"include/public/components/Velocity.hpp"
"include/public/components/Acceleration.hpp"
"include/public/components/Mass.hpp")

set(simulations_src 
"src/World.cpp"
"src/Simulation.cpp")


add_library (Simulation SHARED 
${simulations_private_include}  
${simulations_public_include} 
${simulations_src})

target_compile_features (Simulation PRIVATE cxx_std_17)
target_include_directories(Simulation PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/private")
target_include_directories(Simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
target_link_libraries(Simulation PRIVATE entt)

include(GNUInstallDirs)

install(TARGETS Simulation LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${simulations_public_include} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
