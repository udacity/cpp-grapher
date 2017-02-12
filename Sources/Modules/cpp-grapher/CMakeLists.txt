set(SOURCE_FILES cpp-grapher.cpp ../3rdParty/tinyutf7.h)
add_executable(cpp-grapher ${SOURCE_FILES})

target_link_libraries (cpp-grapher PUBLIC CppGrapher)
