
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

include (rift_python)

add_definitions(-Werror)

rift_pkg_check_modules(UNWIND REQUIRED libunwind>=1.1)
rift_pkg_check_modules(GLIB REQUIRED glib-2.0>=2.42.0)
rift_pkg_check_modules(GOBJECT REQUIRED gobject-2.0>=2.42.0)
rift_pkg_check_modules(GOBJECT_IS REQUIRED gobject-introspection-1.0>=1.42.0)
rift_pkg_check_modules(PEAS REQUIRED libpeas-1.0>=1.12.2)
rift_pkg_check_modules(PYTHON3 REQUIRED python3)

# TODO:  Requires RIFT-5092, cmake runs before protobuf-c is
# installed.
#rift_pkg_check_modules(PROTOBUF_C REQUIRED libprotobuf-c>=1.1.0)

include_directories(
  ${UNWIND_INCLUDE_DIRS}
  ${GLIB_INCLUDE_DIRS}
  #  ${PROTOBUF_C_INCLUDE_DIRS}
  ${GOBJECT_IS_INCLUDE_DIRS}
  ${PEAS_INCLUDE_DIRS}
  ${PYTHON3_INCLUDE_DIRS})

##
# rwlib library targets
##
add_library(rwlib SHARED
  rw_btrace.c
  rw_dl.c
  rw_file.c
  rw_fsm.c
  rw_ip.c
  rwlib.c
  rw_lookup3.c
  rw_proc.c
  rw_radix.c
  rw_rand.c
  rw_resource_annotate.c
  rw_sklist.c
  rw_sys.c
  rw_types.c
  bsd_closefrom.c
  rw_misc_boost.cpp)
target_link_libraries(rwlib PRIVATE
  pthread
  unwind unwind-x86_64 unwind-ptrace unwind-coredump
  ${GLIB_LIBRARIES}
  ${GOBJECT_LIBRARIES}
  ${PYTHON3_LIBRARIES}

  # RIFT-5092 - this should be using pkg_config
  protobuf-c)
  #  ${PROTOBUF_C_LIBRARIES})
add_dependencies(rwlib rwtypes_gi libunwind.a libunwind-x86_64.a libunwind-ptrace.a libunwind-coredump.a)

rift_make_pc(rwlib
  LIBS -lrwlib
  INCLUDEDIRS ${GLIB_INCLUDE_DIRS}
  COMPONENT ${INSTALL_COMPONENT})

##
# rift vx library target
##
add_definitions(-DINSTALLDIR="${CMAKE_INSTALL_PREFIX}")
add_library(rw_vx_plugin SHARED rw_vx_plugin.c)
target_link_libraries(rw_vx_plugin PRIVATE
  rwlib
  rwplugin-1.0
  rwtypes

  pthread

  # RIFT-5112 - using the libpeas suggested libraries causes
  # downstream failures in unittest.
  peas-1.0
  #${PEAS_LIBRARIES}

  ${GOBJECT_IS_LIBRARIES})

##
# Add rwcoredump executable target
##
set(RW_COREDUMP_SOURCES rw_coredump.c)
set(RW_COREDUMP_LIBS unwind unwind-x86_64 unwind-coredump ${PYTHON3_LIBRARIES})
add_executable(rwcoredump ${RW_COREDUMP_SOURCES})
# Specify the link libraries for rwcoredump
target_link_libraries(rwcoredump  ${RW_COREDUMP_LIBS})
# Specificy the targets that the rwcoredump depends on
add_dependencies(rwcoredump libunwind.a libunwind-x86_64.a libunwind-coredump.a )

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/rwcoredump 
  DESTINATION usr/bin
  COMPONENT ${INSTALL_COMPONENT}
)


##
# install the rwlib and rw_vx library
##
install(TARGETS rw_vx_plugin rwlib LIBRARY
  DESTINATION usr/lib COMPONENT ${INSTALL_COMPONENT})
rift_make_pc(rw_vx_plugin
  LIBS -lrw_vx_plugin
  INCLUDEDIRS ${GOBJECT_IS_INCLUDE_DIRS} ${PEAS_INCLUDE_DIRS}
  COMPONENT ${INSTALL_COMPONENT})

install(FILES
    ../include/riftware/rw_cf_type_validate.h
    ../include/riftware/rw_fsm.h
    ../include/riftware/rwlib.h
    ../include/riftware/rw_radix.h
    ../include/riftware/rw_resource_annotate.h
    ../include/riftware/rw_sklist.h
    ../include/riftware/rwtypes.h
    ../include/riftware/rw_dl.h
    ../include/riftware/rw_ip.h
    ../include/riftware/rw_object.h
    ../include/riftware/rw_rand.h
    ../include/riftware/rw_resource_track.h
    ../include/riftware/rw_sys.h
    ../include/riftware/rw_vx_plugin.h
  DESTINATION usr/include COMPONENT ${INSTALL_COMPONENT})

rift_python_install_tree(
  FILES rw_peas.py rw_status.py
  COMPONENT ${INSTALL_COMPONENT})

install(FILES ../include/riftware/rw_cf_type_validate.hpp
  DESTINATION usr/include/c++ COMPONENT ${INSTALL_COMPONENT})

##
# Add a custom target to inlude all the rwlib targets
# The targets that depend on rwlib should use this target
##
add_custom_target(rwlib_targets)
add_dependencies(rwlib_targets rwlib talloc rwplugin-1.0 rwtypes_gi
  rw_vx_plugin)

# Add GI bindings for rw_sys.h
rift_add_introspection(rwlib_gi
  NAMESPACE rwlib
  VERSION 1.0
  HFILES
  ${CMAKE_CURRENT_SOURCE_DIR}/../include/riftware/rw_sys.h
  IDENTIFIER_PREFIX "rw_"
  PACKAGES RwTypes-1.0
  LIBRARIES rwlib rwtypes
  LIBRARY_PATHS
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwtypes/src
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwlib/src
  GIR_PATHS
  ${RIFT_SUBMODULE_BINARY_ROOT}/rwtypes/src
  DEPENDS rwlib
  BUILD_ALL
  )

rift_install_vala_artifacts(
  COMPONENT ${INSTALL_COMPONENT}
  GIR_FILES rwlib-1.0.gir
  TYPELIB_FILES rwlib-1.0.typelib
  LUA_OVERRIDES rwlib.lua
  DEST_PREFIX .
  )
