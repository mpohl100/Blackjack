link_directories(${CMAKE_SOURCE_DIR}/src)

set( EXCEUTABLE_NAME main)
set( PLAYNORMAL_NAME play_normal)

add_executable(${EXCEUTABLE_NAME} main.cpp)
target_link_libraries(${EXCEUTABLE_NAME} blackjack CONAN_PKG::clara)
target_include_directories(${EXCEUTABLE_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(${PLAYNORMAL_NAME} play_normal.cpp)
target_link_libraries(${PLAYNORMAL_NAME} blackjack CONAN_PKG::clara)
target_include_directories(${PLAYNORMAL_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)