
set(SOURCE_FILES CppGrapher.cpp CppGrapher.h Validation/Argument.cpp Validation/DataFile.cpp ../3rdParty/tinyutf8/tinyutf8.cpp ../3rdParty/tinyutf8/tinyutf8.h ../Helpers/Unicode.h)
add_library(CppGrapher ${SOURCE_FILES})

target_include_directories(CppGrapher
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/utf-8/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/tinyutf8/)
