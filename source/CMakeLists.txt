cmake_minimum_required(VERSION 2.6)

# Set the installation directory of the binary file
IF(WIN32)
   SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")
   MESSAGE(STATUS "WIN32")
ELSE()
   SET(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation Directory")
ENDIF()
  
#
# Set the project name.
#
PROJECT (Qt_SensorData)

SET (EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL
  "Where to put the executables")

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE INTERNAL
  "Where to put the libraries")

SET (DEBUG 1)  
 

IF(WIN32)
   # Set the prefix for the debug library
   SET (VAC_DEBUG_PREFIX "_d")
ELSE()
   SET (VAC_DEBUG_PREFIX "") 
ENDIF()

SUBDIRS ( 
  SensorData
  )

# Open the property setting
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET_PROPERTY(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})


# For QT
FIND_PACKAGE (Qt4 REQUIRED)
SET(QT_USE_QTNETWORK TRUE)
INCLUDE (${QT_USE_FILE})
ADD_DEFINITIONS (${QT_DEFINITIONS})