--[[ 
/*
 * 
 *   Copyright 2016 RIFT.IO Inc
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */



  @file   del_shash.lua
  @author Prashanth Bhaskar(prashanth.bhaskar@riftio.com)
  @date   2014/10/17
 
 --]]

local ky = ARGV[1]
local db = tonumber(ARGV[2])
local reply = "FAIL"
--redis.call("SELECT", db)

reply = redis.call("HDEL", KEYS[1], ky)
return reply
