cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project (tvorba-gfx)

SET(tvorba_VERSION_MAJOR 0)
SET(tvorba_VERSION_MINOR 1)
SET(tvorba_VERSION_PATCH 0)
SET(tvorba_VERSION "${tvorba_VERSION_MAJOR}.${tvorba_VERSION_MINOR}.${tvorba_VERSION_PATCH}")

SET(tvorba_VERSION_TAG prealpha)
if(tvorba_VERSION_TAG)
SET(tvorba_VERSION "${tvorba_VERSION}-${tvorba_VERSION_TAG}")
endif()

EXECUTE_PROCESS(COMMAND git rev-parse --short HEAD
                OUTPUT_VARIABLE tvorba_VERSION_BUILD
                ERROR_VARIABLE NONE
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if(tvorba_VERSION_BUILD)
SET(tvorba_VERSION "${tvorba_VERSION}+build.${tvorba_VERSION_BUILD}")
endif()
message("-- Version ${tvorba_VERSION}")


if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE "Release")
endif()

message("-- Build_type: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD STREQUAL "Debug")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
endif()

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})


find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

add_executable(gfx main.cpp events.cpp render.cpp context.cpp entity.cpp)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})
target_link_libraries(gfx ${SDL_LIBRARY} -lm -ldl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})


INSTALL(TARGETS gfx RUNTIME DESTINATION bin)
