cmake_minimum_required (VERSION 3.8)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(simulations_private_include 
"include/private/GalaxyRegistry.hpp")

set(simulations_public_include 
"include/public/IGalaxyRegistry.hpp"
"include/public/Galaxy.hpp"
"include/public/EulerGalaxy.hpp"
"include/public/EulerKromerGalaxy.hpp"
"include/public/CentralDifferenceGalaxy.hpp"
"include/public/VerletGalaxy.hpp"
"include/public/components/Position.hpp"
"include/public/components/Velocity.hpp"
"include/public/components/Acceleration.hpp"
"include/public/components/Mass.hpp"
"include/public/Vector.hpp"
"include/public/IView.hpp")

set(simulations_src 
"src/GalaxyRegistry.cpp"
"src/Galaxy.cpp"
"src/EulerGalaxy.cpp"
"src/EulerKromerGalaxy.cpp"
"src/CentralDifferenceGalaxy.cpp"
"src/VerletGalaxy.cpp"
"src/Vector.cpp")


add_library (Simulation SHARED 
${simulations_private_include}  
${simulations_public_include} 
${simulations_src} "include/private/components/PreAcceleration.hpp")

target_compile_features (Simulation PRIVATE cxx_std_17)
target_include_directories(Simulation PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/private")
target_include_directories(Simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
target_link_libraries(Simulation PRIVATE entt)

include(GNUInstallDirs)

install(TARGETS Simulation LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${simulations_public_include} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
