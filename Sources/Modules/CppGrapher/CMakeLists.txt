set(SOURCE_FILES
        CppGrapher.cpp
        CppGrapher.h
        Validation/Argument.cpp
        Deserialization/KalmanFilterDataFile.cpp
        ${THIRD_PARTY_SOURCE_FILES}
        ${HELPERS_SOURCE_FILES}
        ../RangedGraph/RangedGraph.cpp
        ../RangedGraph/RangedGraph.h)

add_library(CppGrapher ${SOURCE_FILES})

target_compile_definitions(CppGrapher PRIVATE MAGICKCORE_QUANTUM_DEPTH=8 MAGICKCORE_HDRI_ENABLE)

target_include_directories(CppGrapher PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/
        /usr/local/include/ImageMagick-7/)

execute_process(OUTPUT_VARIABLE Q_VERSION
                RESULT_VARIABLE Q_RESULT_CODE
                COMMAND sh ../Scripts/magick_q.sh)

if(Q_RESULT_CODE GREATER 0)
        message(FATAL_ERROR "Error getting ImageMagick Q version. Is ImageMagick 7 installed? You'll need to install from source.")
endif(Q_RESULT_CODE GREATER 0)

target_link_libraries (CppGrapher PUBLIC RangedGraph Magick++-7.Q${Q_VERSION}HDRI)
