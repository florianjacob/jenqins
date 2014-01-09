cmake_minimum_required(VERSION 2.8.8)
project(jenqins)
ADD_DEFINITIONS("-std=c++11")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Can be recuded in cmake 2.8.11, see http://qt-project.org/doc/qt-5.1/qtdoc/cmake-manual.html
# as long is using cmake <2.8.11, remember to adjust qt5_use_modules below
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

set(Communi_DIR "${CMAKE_SOURCE_DIR}/cmake_modules")
ADD_DEFINITIONS(-DIRC_SHARED)
find_package(Communi)

#include_directories(${QT_INCLUDES} ${IRC_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${IRC_INCLUDE_DIR})


file(GLOB_RECURSE jenqins_SRCS_modules 		src/modules/*.cpp)

set(jenqins_SRCS src/botconnection.cpp src/main.cpp ${jenqins_SRCS_modules})

add_executable(jenqins ${jenqins_SRCS})
target_link_libraries(jenqins ${IRC_LIBRARY})
qt5_use_modules(jenqins Core)
qt5_use_modules(jenqins Network)

