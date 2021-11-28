add_subdirectory(evol)

set( LIB_SOURCES Hand.cpp Card52.cpp Util.cpp BlackjackStrategy.cpp Deck52.cpp)

find_package(Threads)
add_library( blackjack SHARED ${LIB_SOURCES} )
target_link_libraries( blackjack CONAN_PKG::range-v3)
target_link_libraries( blackjack evol)
target_link_libraries ( blackjack ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(blackjack PUBLIC {CMAKE_SOURCE_DIR}/src)
target_include_directories(blackjack PUBLIC {CMAKE_SOURCE_DIR}/src/evol)
target_include_directories(blackjack PUBLIC {CMAKE_SOURCE_DIR}/src/par)