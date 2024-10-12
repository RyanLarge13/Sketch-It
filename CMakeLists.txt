cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)

project(sketch_it)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(includes)
link_directories(${GTKMM_LIBRARY_DIRS})

add_definitions(${GTKMM_CFLAGS_OTHER})

file(GLOB_RECURSE SOURCES "src/*.cpp" "lib/*.cpp" "widgets/*.cpp")

add_executable(sketch_it ${SOURCES})

target_link_libraries(sketch_it ${GTKMM_LIBRARIES} OpenGL::GL)
