cmake_minimum_required(VERSION 2.6)
project(Objects)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -ansi -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(OpenGL)
find_package(GLU)
find_package(GLUT)

add_executable(Objects Main.cpp Context.h Object.h Output.h Simulation.h Renderer.h Vector.h Matrix.h)
target_link_libraries(Objects ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLU_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR})
#add_executable(Matrix Testing/Matrix.cpp Matrix.h Vector.h)
#enable_testing()
#add_test(MatrixTest Matrix)
