cmake_minimum_required(VERSION 2.6)

project (FLATWORLD)

include_directories(.)

add_definitions(-g -m32)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -m32")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -m32")

link_directories(/usr/lib)

add_executable(flatWorld
main.cpp slowriter.cpp
phaseZero.cpp phaseOne.cpp phaseTwo.cpp
)

target_link_libraries(flatWorld ncursesw)
