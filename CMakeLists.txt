cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-Wall -Wextra)

# L'exécutable principal
project(ReachabilityGame)

set(TARGET_NAME "ReachabilityGame")

set(SOURCES
    src/main.cpp

    src/Vertex.cpp
)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PUBLIC include)

# Documentation
set(BUILD_DOC FALSE CACHE BOOL "S'il faut construire la documentation ou pas")
if(BUILD_DOC)
    add_subdirectory(docs)
endif(BUILD_DOC)