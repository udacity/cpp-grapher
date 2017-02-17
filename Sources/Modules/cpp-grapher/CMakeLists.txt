set(SOURCE_FILES cpp-grapher.cpp ${THIRD_PARTY_SOURCE_FILES})
add_executable(cpp-grapher ${SOURCE_FILES})

target_link_libraries (cpp-grapher PUBLIC CppGrapher)
target_compile_definitions(cpp-grapher PRIVATE MAGICKCORE_QUANTUM_DEPTH=8 MAGICKCORE_HDRI_ENABLE)
