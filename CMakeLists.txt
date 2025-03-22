cmake_minimum_required(VERSION 3.30)
project(gdclips)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(extern/godot-cpp)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE CLIPS_INCLUDE
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "extern/clips/core/*.h")
file(GLOB_RECURSE CLIPS_SRCS
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "/extern/clips/core/*.c")

add_library(clips SHARED ${CLIPS_INCLUDE})
set_target_properties(clips PROPERTIES LINKER_LANGUAGE CXX)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}}/extern/clips/core" FILES ${CLIPS_SRCS})

add_library(${PROJECT_NAME} SHARED ${SOURCES}
        src/gdclips.h)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC extern/godot-cpp/gen/include)
target_include_directories(${PROJECT_NAME} PUBLIC extern/clips/core)
target_link_libraries(${PROJECT_NAME} PUBLIC godot::cpp clips)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX src FILES ${SOURCES})
