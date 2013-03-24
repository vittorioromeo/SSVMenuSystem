# -*- cmake -*-

# - Find SSVUtils
# Find the SSVUtils includes and library
# This module defines
# SSVMENUSYSTEM_INCLUDE_DIR, where to find SSVUtils headers.
# SSVMENUSYSTEM_LIBRARIES, the libraries needed to use SSVUtils.
# SSVMENUSYSTEM_FOUND, If false, do not try to use SSVUtils.
# also defined, but not for general use are
# SSVMENUSYSTEM_LIBRARY, where to find the SSVUtils library.

FIND_PATH(SSVMENUSYSTEM_INCLUDE_DIR
  NAMES SSVMenuSystem/SSVMenuSystem.h
  PATH_SUFFIXES include/
  PATHS "${PROJECT_SOURCE_DIR}/../SSVMenuSystem/"
  "${PROJECT_SOURCE_DIR}/extlibs/SSVMenuSystem/"
  ${SSVMENUSYSTEM_ROOT}
  $ENV{SSVMENUSYSTEM_ROOT}
  /usr/local/
  /usr/
  /sw/         # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
)

message("\nFound SSVMenuSystem include at: ${SSVMENUSYSTEM_INCLUDE_DIR}.\n")

FIND_LIBRARY(SSVMENUSYSTEM_LIBRARY
  NAMES SSVMenuSystem libSSVMenuSystem SSVMenuSystem-s libSSVMenuSystem-s ssvmenusystem libssvmenusystem ssvmenusystem-s libssvmenusystem-s
  PATH_SUFFIXES lib/ lib64/
  PATHS "${PROJECT_SOURCE_DIR}/../SSVMenuSystem/"
  "${PROJECT_SOURCE_DIR}/extlibs/SSVMenuSystem/"
  ${SSVMENUSYSTEM_ROOT}
  $ENV{SSVMENUSYSTEM_ROOT}
  /usr/local/
  /usr/
  /sw/         # Fink
  /opt/local/  # DarwinPorts
  /opt/csw/    # Blastwave
  /opt/
)

message("\nFound SSVMenuSystem library at: ${SSVMENUSYSTEM_LIBRARY}.\n")

IF (SSVMENUSYSTEM_LIBRARY AND SSVMENUSYSTEM_INCLUDE_DIR)
    SET(SSVMENUSYSTEM_LIBRARIES ${SSVMENUSYSTEM_LIBRARY})
    SET(SSVMENUSYSTEM_FOUND TRUE)
ELSE (SSVMENUSYSTEM_LIBRARY AND SSVMENUSYSTEM_INCLUDE_DIR)
    SET(SSVMENUSYSTEM_FOUND FALSE)
ENDIF (SSVMENUSYSTEM_LIBRARY AND SSVMENUSYSTEM_INCLUDE_DIR)

IF (SSVMENUSYSTEM_FOUND)
      MESSAGE(STATUS "Found SSVMenuSystem in ${SSVMENUSYSTEM_INCLUDE_DIR}")
ELSE (SSVMENUSYSTEM_FOUND)
   IF (SSVMENUSYSTEM_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find SSVMenuSystem library")
   ENDIF (SSVMENUSYSTEM_FIND_REQUIRED)
ENDIF (SSVMENUSYSTEM_FOUND)

MARK_AS_ADVANCED(
  SSVMENUSYSTEM_LIBRARY
  SSVMENUSYSTEM_INCLUDE_DIR
)
