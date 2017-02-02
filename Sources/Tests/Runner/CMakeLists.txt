include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Catch/include)
set(SOURCE_FILES Runner.cpp)
add_library(Runner ${SOURCE_FILES})
