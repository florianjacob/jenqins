find_package(Qt4)
include( ${QT_USE_FILE} )

FIND_LIBRARY(IRC_LIBRARY NAMES IrcCore PATHS ${QT_LIBRARY_DIR})
FIND_PATH(IRC_INCLUDE_DIR NAMES "ircglobal.h" PATHS ${QT_INCLUDE_DIR} PATH_SUFFIXES Communi/IrcCore)

# message( STATUS ${IRC_LIBRARY})
if( IRC_LIBRARY AND IRC_INCLUDE_DIR )
    message( STATUS "Found libCommuni ${IRC_LIBRARY}, ${IRC_INCLUDE_DIR}")
    set( IRC_FOUND 1 )
else()
    message( STATUS "Could NOT find libCommuni" )
endif()
