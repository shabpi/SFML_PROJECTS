cmake_minimum_required(VERSION 3.28)
project(SFMLPROJECTS LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(RandomLadybug src/RandomLadybug.cpp)
add_executable(ArthemeticGame src/ArthemeticGame.cpp)
add_executable(Graphicalcalc src/Graphicalcalc.cpp)


target_compile_features(RandomLadybug PRIVATE cxx_std_17)
target_link_libraries(RandomLadybug PRIVATE SFML::Graphics)


target_compile_features(Graphicalcalc PRIVATE cxx_std_17)
target_link_libraries(Graphicalcalc PRIVATE SFML::Graphics)

target_compile_features(ArthemeticGame  PRIVATE cxx_std_17)
target_link_libraries(ArthemeticGame  PRIVATE SFML::Graphics)
