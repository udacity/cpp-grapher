set(SOURCE_FILES
        CppGrapher.cpp
        CppGrapher.h
        Validation/Argument.cpp
        Validation/DataFile.cpp
        Graphing/Visualization.cpp
        ${THIRD_PARTY_SOURCE_FILES}
        ${HELPERS_SOURCE_FILES})

add_library(CppGrapher ${SOURCE_FILES})

target_compile_definitions(CppGrapher PRIVATE MAGICKCORE_QUANTUM_DEPTH=8 MAGICKCORE_HDRI_ENABLE)
target_include_directories(CppGrapher PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/tinyutf8/
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/
        /usr/local/include/ImageMagick-7/)

target_link_libraries (CppGrapher PUBLIC Magick++-7.Q8HDRI)
