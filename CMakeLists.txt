project(CommuniBot)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED COMPONENTS QtCore QtNetwork)

set(Communi_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
ADD_DEFINITIONS(-DCOMMUNI_STATIC)
find_package(Communi)

include_directories(${QT_INCLUDES} ${IRC_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set(CommuniBot_SRCS src/ircbot.cpp src/main.cpp)
qt4_automoc(${CommuniBot_SRCS})
add_executable(CommuniBot ${CommuniBot_SRCS})
target_link_libraries(CommuniBot ${IRC_LIBRARY} ${QT_QTCORE_LIBRARY})

install(TARGETS CommuniBot RUNTIME DESTINATION bin)
add_subdirectory(src)