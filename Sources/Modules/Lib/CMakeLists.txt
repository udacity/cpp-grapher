set(SOURCE_FILES Lib.cpp Lib.h)
add_library(Lib ${SOURCE_FILES})

target_include_directories(Lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/utf-8/)
