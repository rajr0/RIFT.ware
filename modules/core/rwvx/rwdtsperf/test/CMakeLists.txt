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
# Author(s): Tim Mortsolf
# Creation Date: 2014/03/20
# 

cmake_minimum_required(VERSION 2.8)

add_custom_target(run_rwdtsperf
  COMMAND
    cd ${CMAKE_INSTALL_PREFIX} &&
    ${PROJECT_TOP_DIR}/scripts/env/envset.sh
      "GDB=1"
      "VERBOSE=1"
      "RWMAIN_CMDARGS=--collapse-all"
      ${CMAKE_INSTALL_PREFIX}/usr/bin/rwmain
        load manifest file ${CMAKE_CURRENT_SOURCE_DIR}/rw-manifest.xml
)
