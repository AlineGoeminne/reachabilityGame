set(TESTS_SOURCES
    main.cpp

    types/Long.cpp
    types/DynamicPriorityQueue.cpp
)

set(TESTS_NAME ${TARGET_NAME}-tests)
add_executable(${TESTS_NAME} ${TESTS_SOURCES})
target_include_directories(${TESTS_NAME} PUBLIC .)
target_link_libraries(${TESTS_NAME} ${LIBRARY_NAME})