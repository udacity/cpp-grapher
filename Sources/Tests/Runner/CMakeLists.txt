set(TEST_RUNNER_SOURCE_FILES Runner.cpp)
add_library(Runner ${TEST_RUNNER_SOURCE_FILES})
target_include_directories(Runner PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Catch/include)


