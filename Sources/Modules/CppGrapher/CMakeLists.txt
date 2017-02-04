set(SOURCE_FILES
        CppGrapher.cpp
        CppGrapher.h
        Validation/Argument.cpp
        Validation/DataFile.cpp
        ${THIRD_PARTY_SOURCE_FILES}
        ${HELPERS_SOURCE_FILES})

add_library(CppGrapher ${SOURCE_FILES})

target_include_directories(CppGrapher PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/tinyutf8/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/)
