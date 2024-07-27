cmake_minimum_required(VERSION 3.10)

project(OpenGLProject)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

include_directories(include)
file(GLOB SOURCES src/*.cpp)
add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE OpenGL::GL)
target_link_libraries(main PRIVATE glfw)
target_link_libraries(main PRIVATE glad::glad)
target_link_libraries(main PRIVATE glm::glm)
target_link_libraries(main PRIVATE assimp::assimp)

set(ASSET_DIR assets)
set(ASSET_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${ASSET_DIR})

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/${ASSET_DIR} ${ASSET_OUTPUT_DIR}
)
