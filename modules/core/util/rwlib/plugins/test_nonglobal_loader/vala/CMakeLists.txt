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
# Creation Date: 12/08/2014
# 

##
# Set some RIFT specific VALA variables for this cmake project
##
set(VALA_NAME test_nonglobal_loader)
set(VALA_FILES ${VALA_NAME}.vala)
set(VALA_VERSION 1.0)
set(VALA_RELEASE 1)
set(VALA_LONG_NAME ${VALA_NAME}-${VALA_VERSION})
set(VALA_TYPELIB_PREFIX TestNonglobalLoader-${VALA_VERSION})

##
# This function compiles all the vala sources
# Generates the package .h/.c sources, .gir file, .vapi file, and the .so
##
rift_add_vala(
  ${VALA_LONG_NAME}
  VALA_FILES ${VALA_FILES}
  GENERATE_HEADER_FILE ${VALA_NAME}.h
  GENERATE_SO_FILE lib${VALA_LONG_NAME}.so
  GENERATE_VAPI_FILE ${VALA_LONG_NAME}.vapi
  GENERATE_GIR_FILE ${VALA_TYPELIB_PREFIX}.gir
  GENERATE_TYPELIB_FILE ${VALA_TYPELIB_PREFIX}.typelib
  )

##
# This function creates an install target for artifacts generated from the vala files
##
rift_install_vala_artifacts(
  COMPONENT ${INSTALL_COMPONENT}
  HEADER_FILES ${VALA_NAME}.h
  SO_FILES lib${VALA_LONG_NAME}.so
  VAPI_FILES ${VALA_LONG_NAME}.vapi
  GIR_FILES ${VALA_TYPELIB_PREFIX}.gir
  TYPELIB_FILES ${VALA_TYPELIB_PREFIX}.typelib
  DEST_PREFIX .
  )

# Recurse into the subdirectories 
# This does not actually cause another cmake executable to run
# The same process will walk through the project's entire directory structure
set(subdirs 
  ${VALA_NAME}-lua
  )
rift_add_subdirs(SUBDIR_LIST ${subdirs})
