set(SOURCE_FILES cpp-grapher.cpp)
add_executable(cpp-grapher ${SOURCE_FILES})

target_include_directories(cpp-grapher
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../CppGrapher/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/utf-8/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/tinyutf8/)

target_link_libraries (cpp-grapher PUBLIC CppGrapher)
