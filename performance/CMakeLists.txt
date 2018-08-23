set(PERFORMANCE_NAME ${TARGET_NAME}-perf)

add_executable(${PERFORMANCE_NAME}-naive naiveTests.cpp)
target_include_directories(${PERFORMANCE_NAME}-naive PUBLIC include)
target_include_directories(${PERFORMANCE_NAME}-naive PUBLIC .)
target_link_libraries(${PERFORMANCE_NAME}-naive ${LIBRARY_NAME})

add_executable(${PERFORMANCE_NAME}-tree treeTests.cpp)
target_include_directories(${PERFORMANCE_NAME}-tree PUBLIC include)
target_include_directories(${PERFORMANCE_NAME}-tree PUBLIC .)
target_link_libraries(${PERFORMANCE_NAME}-tree ${LIBRARY_NAME})