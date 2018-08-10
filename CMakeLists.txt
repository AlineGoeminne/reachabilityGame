cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_definitions(-Wall -Wextra)

# L'exécutable principal
project(ReachabilityGame)

set(TARGET_NAME "ReachabilityGame")
set(LIBRARY_NAME ${TARGET_NAME}-lib)

set(SOURCES
    src/Vertex.cpp

    src/types/Long.cpp
)

add_library(${LIBRARY_NAME} ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC include)

add_executable(${TARGET_NAME} src/main.cpp)
target_link_libraries(${TARGET_NAME} ${LIBRARY_NAME})

# Documentation
set(BUILD_DOC FALSE CACHE BOOL "S'il faut construire la documentation ou pas")
if(BUILD_DOC)
    add_subdirectory(docs)
endif(BUILD_DOC)

set(BUILD_TESTS FALSE CACHE BOOL "S'il faut construire les tests ou pas")
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)