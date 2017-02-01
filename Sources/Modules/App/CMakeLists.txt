set(SOURCE_FILES App.cpp App.h main.cpp)

target_include_directories(Lib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/any/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/Optional/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/variant/
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty/utf-8/)

add_executable(App ${SOURCE_FILES})
target_link_libraries (App PUBLIC Lib)
