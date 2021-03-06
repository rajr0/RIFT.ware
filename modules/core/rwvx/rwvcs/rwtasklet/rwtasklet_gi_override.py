
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

import gi.module
import rift.gi_utils

def wrap_rwtasklet():
    gi_mod = gi.module.get_introspection_module('RwTasklet')
    info_cls = gi_mod.Info

    prop_nd_getter = {
        'instance_name': gi_mod.Info.get_instance_name,
        'parent_vm_instance_name': gi_mod.Info.get_parent_vm_instance_name,
        'rwsched_instance': gi_mod.Info.get_rwsched_instance,
        'rwsched_tasklet': gi_mod.Info.get_rwsched_tasklet,
    }
    for prop, getter in prop_nd_getter.items():
        rift.gi_utils.create_property(gi_mod.Info, prop, getter)

    def __str__(self):
        return "TaskletInfo(instance_name=%s)" % (self.instance_name,)
    gi_mod.Info.__str__ = __str__


wrap_rwtasklet()

# vim: sw=4
