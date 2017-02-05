set(SOURCE_FILES cpp-grapher.cpp)
add_executable(cpp-grapher ${SOURCE_FILES})

target_link_libraries (cpp-grapher PUBLIC CppGrapher)
