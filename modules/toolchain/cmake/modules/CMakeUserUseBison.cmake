
# 
#   Copyright 2016 RIFT.IO Inc
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

# - Look for GNU Bison, the parser generator
# Based off a news post from Andy Cedilnik at Kitware
# Defines the following:
#  BISON_EXECUTABLE - path to the bison executable
#  BISON_FILE - parse a file with bison
#  BISON_PREFIX_OUTPUTS - Set to true to make BISON_FILE produce prefixed
#                         symbols in the generated output based on filename.
#                         So for ${filename}.y, you'll get ${filename}parse(), etc.
#                         instead of yyparse().
#  BISON_GENERATE_DEFINES - Set to true to make BISON_FILE output the matching
#                           .h file for a .c file. You want this if you're using
#                           flex.

IF(NOT DEFINED BISON_PREFIX_OUTPUTS)
 SET(BISON_PREFIX_OUTPUTS FALSE)
ENDIF(NOT DEFINED BISON_PREFIX_OUTPUTS)

IF(NOT DEFINED BISON_GENERATE_DEFINES)
 SET(BISON_GENERATE_DEFINES FALSE)
ENDIF(NOT DEFINED BISON_GENERATE_DEFINES)

IF(NOT BISON_EXECUTABLE)
 MESSAGE(STATUS "Looking for bison")
 FIND_PROGRAM(BISON_EXECUTABLE bison)
 IF(BISON_EXECUTABLE)
   MESSAGE(STATUS "Looking for bison -- ${BISON_EXECUTABLE}")
 ENDIF(BISON_EXECUTABLE)
 MARK_AS_ADVANCED(BISON_EXECUTABLE)
ENDIF(NOT BISON_EXECUTABLE)

IF(BISON_EXECUTABLE)
 MACRO(BISON_FILE FILENAME)
   GET_FILENAME_COMPONENT(PATH "${FILENAME}" PATH)
   IF("${PATH}" STREQUAL "")
     SET(PATH_OPT "")
   ELSE("${PATH}" STREQUAL "")
     SET(PATH_OPT "/${PATH}")
   ENDIF("${PATH}" STREQUAL "")
   GET_FILENAME_COMPONENT(HEAD "${FILENAME}" NAME_WE)
   IF(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}${PATH_OPT}")
     FILE(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}${PATH_OPT}")
   ENDIF(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}${PATH_OPT}")
   IF(BISON_PREFIX_OUTPUTS)
     SET(PREFIX "${HEAD}")
   ELSE(BISON_PREFIX_OUTPUTS)
     SET(PREFIX "yy")
   ENDIF(BISON_PREFIX_OUTPUTS)
   SET(OUTFILE "${CMAKE_CURRENT_BINARY_DIR}${PATH_OPT}/${HEAD}.tab.c")
   IF(BISON_GENERATE_DEFINES)
     SET(HEADER "${CMAKE_CURRENT_BINARY_DIR}${PATH_OPT}/${HEAD}.tab.h")
     ADD_CUSTOM_COMMAND(
       OUTPUT "${OUTFILE}" "${HEADER}"
       COMMAND "${BISON_EXECUTABLE}"
       ARGS "--name-prefix=${PREFIX}"
       "--defines"
       "--output-file=${OUTFILE}"
       "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}"
       DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
     SET_SOURCE_FILES_PROPERTIES("${OUTFILE}" "${HEADER}" PROPERTIES GENERATED TRUE)
     SET_SOURCE_FILES_PROPERTIES("${HEADER}" PROPERTIES HEADER_FILE_ONLY TRUE)
   ELSE(BISON_GENERATE_DEFINES)
     ADD_CUSTOM_COMMAND(
       OUTPUT "${OUTFILE}"
       COMMAND "${BISON_EXECUTABLE}"
       ARGS "--name-prefix=${PREFIX}"
       "--output-file=${OUTFILE}"
       "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}"
       DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}")
     SET_SOURCE_FILES_PROPERTIES("${OUTFILE}" PROPERTIES GENERATED TRUE)
   ENDIF(BISON_GENERATE_DEFINES)
 ENDMACRO(BISON_FILE) 
ENDIF(BISON_EXECUTABLE)
