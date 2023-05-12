set(TESTS
    lfs_tests.cpp
)

add_executable(gtests ${TESTS})
target_link_libraries(gtests lfs gtest gtest_main pthread)
target_include_directories(gtests PRIVATE ${PROJECT_SOURCE_DIR} ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
