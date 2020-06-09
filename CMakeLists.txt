cmake_minimum_required(VERSION 2.8)


project(Gasg)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


set(ALL_LIBS
        ${OPENGL_LIBRARY}
        #${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
)

include_directories(include)
include_directories("${GLFW_INCLUDE_DIRS}/GLFW")
include_directories(${GLEW_INCLUDE_DIRS})

file(GLOB_RECURSE HEADERS "include/*.h*")
file(GLOB_RECURSE SOURCES "src/*.cpp")

message("GLFW INCLUDE: ${GLFW_INCLUDE_DIRS}")

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} "main.cpp"  ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS} glfw)
