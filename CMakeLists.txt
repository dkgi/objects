cmake_minimum_required(VERSION 2.6)
project(objects)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -ansi -g -std=gnu++0x")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(OpenGL)
find_package(GLUT)
find_package(Boost)

add_executable(objects config.h main.cc context.h camera.h object.h mesh.h
    mesh.cc  simulation.h renderer.h vector.h matrix.h)
target_link_libraries(objects ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLU_LIBRARIES} ${BOOST_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR})
#add_executable(Matrix Testing/Matrix.cpp Matrix.h Vector.h)
#enable_testing()
#add_test(MatrixTest Matrix)
