find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

FIND_LIBRARY(IRC_LIBRARY NAMES IrcCore)
FIND_PATH(IRC_INCLUDE_DIR NAMES "ircglobal.h" PATH_SUFFIXES IrcCore Communi/IrcCore)

# message( STATUS ${IRC_LIBRARY})
if( IRC_LIBRARY AND IRC_INCLUDE_DIR )
    message( STATUS "Found libCommuni ${IRC_LIBRARY}, ${IRC_INCLUDE_DIR}")
    set( IRC_FOUND 1 )
else()
    message( STATUS "Could NOT find libCommuni" )
endif()
