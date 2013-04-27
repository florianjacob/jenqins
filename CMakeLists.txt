project(jenqins)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED COMPONENTS QtCore QtNetwork)

set(Communi_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
ADD_DEFINITIONS(-DCOMMUNI_SHARED)
find_package(Communi)

include_directories(${QT_INCLUDES} ${IRC_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE jenqins_SRCS_modules 		src/modules/*.cpp)

set(jenqins_SRCS src/botsession.cpp src/main.cpp ${jenqins_SRCS_modules})
qt4_automoc(${jenqins_SRCS})
add_executable(jenqins ${jenqins_SRCS})
target_link_libraries(jenqins ${IRC_LIBRARY} ${QT_QTCORE_LIBRARY})

install(TARGETS jenqins RUNTIME DESTINATION bin)
add_subdirectory(src)
