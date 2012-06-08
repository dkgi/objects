cmake_minimum_required(VERSION 2.6)
project(objects)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -ansi -g -std=gnu++0x")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

find_package(OpenGL)
find_package(GLUT)
find_package(Boost 1.41 COMPONENTS system filesystem REQUIRED)

add_executable(objects 
		config.h main.cc object.h object.cc simulation.h
    parser.h parser.cc log.h
    context.h camera.h renderer.h renderer.cc
    shape.h shape.cc mesh.h mesh.cc 
    vector.h matrix.h
)

target_link_libraries(objects
		${OPENGL_LIBRARIES} 
		${GLUT_LIBRARIES}
		${Boost_LIBRARIES}
)

