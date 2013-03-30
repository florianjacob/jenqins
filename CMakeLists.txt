project(CommuniBot)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(CommuniBot_SRCS CommuniBot.cpp main.cpp)
qt4_automoc(${CommuniBot_SRCS})
add_executable(CommuniBot ${CommuniBot_SRCS})
target_link_libraries(CommuniBot ${QT_QTCORE_LIBRARY})

install(TARGETS CommuniBot RUNTIME DESTINATION bin)
