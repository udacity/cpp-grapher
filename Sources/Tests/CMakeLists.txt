add_subdirectory(Unit)
add_subdirectory(Integration)
add_subdirectory(Performance)
add_subdirectory(System)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Catch/include)

set(SOURCE_FILES Runner.Tests/CatchMain.cpp ${UNIT_TEST_SOURCE_FILES} ${INTEGRATION_TEST_SOURCE_FILES} ${PERFORMANCE_SOURCE_FILES} ${SYSTEM_TEST_SOURCE_FILES})
add_executable(Tests ${SOURCE_FILES})

target_link_libraries (Tests PUBLIC Lib)
