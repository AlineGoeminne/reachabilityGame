set(PERFORMANCE_SOURCES
    main.cpp
)

set(PERFORMANCE_NAME ${TARGET_NAME}-perf)
add_executable(${PERFORMANCE_NAME} ${PERFORMANCE_SOURCES})
target_include_directories(${PERFORMANCE_NAME} PUBLIC include)
target_link_libraries(${PERFORMANCE_NAME} ${LIBRARY_NAME})