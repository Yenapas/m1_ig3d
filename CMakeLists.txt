project(m1_ig3d)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -ggdb -O0 -Wall -Wextra")

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/GL)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/GL)

include_directories(${OPENGL_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)
link_directories(${CMAKE_SOURCE_DIR}/dependencies/GLFW)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} "-lGLEW -lglfw3" ${OPENGL_LIBRARIES} ${X11_LIBRARIES} "-lXi -lXrandr -lXinerama -lXxf86vm -lXcursor -ldl -pthread")
