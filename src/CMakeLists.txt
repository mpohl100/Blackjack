set( LIB_SOURCES Hand.cpp Card52.cpp Util.cpp)

add_library( blackjack SHARED ${LIB_SOURCES} )
target_link_libraries( blackjack CONAN_PKG::range-v3)
target_include_directories(blackjack PUBLIC {CMAKE_SOURCE_DIR}/src)