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
# Author(s): Anil Gunturu
# Creation Date: 8/29/2013
# 

# This module looks for gobject-introspection,
#  and sets the following variables
# RIFT_LIBUNWIND_FOUND         - set to 1 if module(s) exist
# RIFT_LIBUNWIND_LIBRARIES     - only the libraries (w/o the '-l')
# RIFT_LIBUNWIND_LIBRARY_DIRS  - the paths of the libraries (w/o the '-L')
# RIFT_LIBUNWIND_LDFLAGS       - all required linker flags
# RIFT_LIBUNWIND_LDFLAGS_OTHER - all other linker flags
# RIFT_LIBUNWIND_INCLUDE_DIRS  - the '-I' preprocessor flags (w/o the '-I')
# RIFT_LIBUNWIND_CFLAGS        - all required cflags
# RIFT_LIBUNWIND_CFLAGS_OTHER  - the other compiler flags

cmake_minimum_required(VERSION 2.8)

include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
  message(FATAL_ERROR "PKG CONFIG NOT FOUND")
endif()

# This cmake function searches the .pc files 
# and sets the above mentioned varibales
pkg_check_modules(RIFT_LIBUNWIND libunwind)

set(DEBUG_FindRIFT_LIBUNWIND 0)
if(DEBUG_FindRIFT_LIBUNWIND)
  message("RIFT_LIBUNWIND_FOUND = ${RIFT_LIBUNWIND_FOUND}")
  message("RIFT_LIBUNWIND_LIBRARIES = ${RIFT_LIBUNWIND_LIBRARIES}")
  message("RIFT_LIBUNWIND_LIBRARY_DIRS = ${RIFT_LIBUNWIND_LIBRARY_DIRS}")
  message("RIFT_LIBUNWIND_LDFLAGS = ${RIFT_LIBUNWIND_LDFLAGS}")
  message("RIFT_LIBUNWIND_LDFLAGS_OTHER = ${RIFT_LIBUNWIND_LDFLAGS_OTHER}")
  message("RIFT_LIBUNWIND_INCLUDE_DIRS = ${RIFT_LIBUNWIND_INCLUDE_DIRS}")
  message("RIFT_LIBUNWIND_CFLAGS = ${RIFT_LIBUNWIND_CFLAGS}")
  message("RIFT_LIBUNWIND_CFLAGS_OTHER = ${RIFT_LIBUNWIND_CFLAGS_OTHER}")
endif()