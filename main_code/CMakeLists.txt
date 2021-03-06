###########################################################################
#   Copyright (C) 2020 MUTHUKUMARAVEL
#   Author             : MUTHUKUMARAVEL 
#   github username    : muthu-kumaravel
#   github email       : muthukumaravel.muthuraman@gmail.com
###########################################################################

cmake_minimum_required (VERSION 3.5.0)

#######
# Project name & version
######
project (BasicImageLibrary)

#######
# Define user options
######
option(DEBUG "Build Basic Image Library in DEBUG mode" OFF)

#######
# Set necessary flags
######
if(WIN32)
elseif(WIN32)
set(CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-g -std=gnu++11")
set(CMAKE_BUILD_TYPE "Release")
endif(WIN32)
if(APPLE)
  set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -std=gnu++11")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -std=gnu++11 -fopenmp")
endif()

if(WIN32)
  if(DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  else(DEBUG)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  endif(DEBUG)
endif(WIN32)

######
# Identify system architecture
#####
if(UNIX)
  EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
elseif(WIN32)
  set(ARCHITECTURE "x86_64")
endif()

#######
# Set essential flags for DEBUG build
######
if (DEBUG)
  set(CMAKE_VERBOSE_MAKEFILE ON)
  add_definitions(-DBIL_DEBUG=1)
  set(CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
else (DEBUG)
  MESSAGE( STATUS "variable is: " ${CXX_FLAGS} )
  set(CXX_FLAGS "${CXX_FLAGS} ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
endif (DEBUG)

#####
# Include directories
#####
include_directories("${PROJECT_SOURCE_DIR}/includes/core"
                    "${PROJECT_SOURCE_DIR}/includes/basic_functions"
                    "${PROJECT_SOURCE_DIR}/includes/math_functions"
                    "${PROJECT_SOURCE_DIR}/includes/adobe_functions")

#####
# Source files
#####
file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/basic_functions/*.cpp"
                    "${PROJECT_SOURCE_DIR}/src/math_functions/*.cpp"
                    "${PROJECT_SOURCE_DIR}/src/adobe_functions/*.cpp")

#####
# Set Basic Image library generation path
#####
if (WIN32)
  set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)
else (WIN32)
  if(DEBUG)  
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib/Debug)
  else(DEBUG)  
    set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib/Release)
  endif(DEBUG)
endif (WIN32)


#####
# Build Basic Image core library
#####
add_library(basic_image_core STATIC ${SRC_FILES})

#####
# Link dependency libs with basic image lib
#####
set(BASIC_IMAGE_CORE ${LIBRARY_OUTPUT_PATH}/libbasic_image_core.a)

#####
# Build Basic Image library with all its dependencies linked statically
#####
if (WIN32)
  set_target_properties(basic_image_core PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
elseif (UNIX AND NOT APPLE AND NOT ${ARCHITECTURE} STREQUAL "aarch64")
  set_target_properties(basic_image_core PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  add_custom_command(OUTPUT ${LIBRARY_OUTPUT_PATH}/libbasic_image.a
                      COMMAND ar ARGS -x ${BASIC_IMAGE_CORE}
                      COMMAND rm ARGS -f ${BASIC_IMAGE_CORE}
                      COMMAND ar ARGS -r ${LIBRARY_OUTPUT_PATH}/libbasic_image.a *.o
                      COMMAND rm ARGS -f *.o
                      DEPENDS "basic_image_core")

  add_custom_target(basic_image ALL DEPENDS ${LIBRARY_OUTPUT_PATH}/libbasic_image.a)
elseif(APPLE OR ${ARCHITECTURE} STREQUAL "aarch64")
  add_library(basic_image STATIC ${SRC_FILES})
endif()
###############################################################################