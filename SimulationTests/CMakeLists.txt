﻿cmake_minimum_required (VERSION 3.8)

add_executable (SimulationTests 
"helpers/StubView.hpp"
"helpers/StubView.cpp"
"Tests.cpp"
"GravityTests.cpp")

target_compile_features (SimulationTests PRIVATE cxx_std_14)
target_link_libraries(SimulationTests PRIVATE catch2 PRIVATE Simulation)
