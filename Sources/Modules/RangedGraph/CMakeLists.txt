set(SOURCE_FILES
        RangedGraph.cpp
        RangedGraph.h
        ${THIRD_PARTY_SOURCE_FILES}
        ${HELPERS_SOURCE_FILES})

add_library(RangedGraph ${SOURCE_FILES})

target_compile_definitions(RangedGraph PRIVATE MAGICKCORE_QUANTUM_DEPTH=8 MAGICKCORE_HDRI_ENABLE)
target_include_directories(RangedGraph PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/
        /usr/local/include/ImageMagick-7/)

target_link_libraries (RangedGraph PUBLIC Magick++-7.Q8HDRI)
