

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



/**
 * @file rwtermio-c.in.c
 * @author Autogenerated
 * @date 08/25/2015
 * @brief TerminalIO Tasklet plugin 
 */

#include "rwtermio-c.h"

RW_CF_TYPE_DEFINE("Rwtermio tasklet component type", rwtermio_component_ptr_t);

RW_CF_TYPE_DEFINE("Rwtermio tasklet instance type", rwtermio_instance_ptr_t);

RwTaskletPluginComponentHandle *rwtermio__component__component_init(RwTaskletPluginComponent *self)
{
  rwtermio_component_ptr_t component;
  RwTaskletPluginComponentHandle *h_component;
  gpointer handle;

  // Register the RW.Init types
  RW_CF_TYPE_REGISTER(rwtermio_component_ptr_t);
  RW_CF_TYPE_REGISTER(rwtermio_instance_ptr_t);

  // Allocate a new rwtermio_component structure
  component = rwtermio_component_init();
  RW_CF_TYPE_VALIDATE(component, rwtermio_component_ptr_t);

  // Allocate a gobject for the handle
  handle = g_object_new(RW_TASKLET_PLUGIN_TYPE_COMPONENT_HANDLE, 0);
  h_component = RW_TASKLET_PLUGIN_COMPONENT_HANDLE(handle);
  h_component->priv = (gpointer) component;

  // Return the handle to the rwtasklet component
  return h_component;
}

void rwtermio__component__component_deinit(
        RwTaskletPluginComponent *self,
        RwTaskletPluginComponentHandle *h_component)
{
}

static RwTaskletPluginInstanceHandle *rwtermio__component__instance_alloc(
        RwTaskletPluginComponent *self, 
        RwTaskletPluginComponentHandle *h_component, 
        struct rwtasklet_info_s *tasklet_info, 
        RwTaskletPlugin_RWExecURL *instance_url)
{
  rwtermio_component_ptr_t component;
  rwtermio_instance_ptr_t  instance;
  RwTaskletPluginInstanceHandle *h_instance;
  gpointer handle;

  // Validate input parameters
  component = (rwtermio_component_ptr_t) h_component->priv;
  RW_CF_TYPE_VALIDATE(component, rwtermio_component_ptr_t);

  // Allocate a new rwtermio_instance structure
  instance = rwtermio_instance_alloc(component, tasklet_info, instance_url);
  RW_CF_TYPE_VALIDATE(instance, rwtermio_instance_ptr_t);
  instance->component = component;

  // Allocate a gobject for the handle
  handle = g_object_new(RW_TASKLET_PLUGIN_TYPE_INSTANCE_HANDLE, 0);
  h_instance = RW_TASKLET_PLUGIN_INSTANCE_HANDLE(handle);
  h_instance->priv = (gpointer) instance;

  // Return the handle to the rwtasklet instance
  return h_instance;
}

void rwtermio__component__instance_free(
        RwTaskletPluginComponent *self,
        RwTaskletPluginComponentHandle *h_component,
        RwTaskletPluginInstanceHandle *h_instance)
{
}

static void rwtermio__component__instance_start(
        RwTaskletPluginComponent *self, 
        RwTaskletPluginComponentHandle *h_component, 
        RwTaskletPluginInstanceHandle *h_instance)
{
  rwtermio_component_ptr_t component;
  rwtermio_instance_ptr_t  instance;

  // Validate input parameters
  component = (rwtermio_component_ptr_t) h_component->priv;
  RW_CF_TYPE_VALIDATE(component, rwtermio_component_ptr_t);

  instance = (rwtermio_instance_ptr_t) h_instance->priv;
  RW_CF_TYPE_VALIDATE(instance, rwtermio_instance_ptr_t);

  // Call the tasklet instance start routine
  rwtermio_instance_start(component, instance);

  RWTRACE_INFO(instance->rwtasklet_info->rwtrace_instance,
               RWTRACE_CATEGORY_RWTASKLET,
               "rwtermio -- tasklet [%d] is started!",
               instance->rwtasklet_info->identity.rwtasklet_instance_id);

}

static void rwtermio__component__instance_stop(
        RwTaskletPluginComponent *self, 
        RwTaskletPluginComponentHandle *h_component, 
        RwTaskletPluginInstanceHandle *h_instance)
{
  rwtermio_component_ptr_t component;
  rwtermio_instance_ptr_t  instance;

  // Validate input parameters
  component = (rwtermio_component_ptr_t) h_component->priv;
  RW_CF_TYPE_VALIDATE(component, rwtermio_component_ptr_t);

  instance = (rwtermio_instance_ptr_t) h_instance->priv;
  RW_CF_TYPE_VALIDATE(instance, rwtermio_instance_ptr_t);
}


static void rwtermio_c_extension_init(RwtermioCExtension *plugin)
{
}

static void rwtermio_c_extension_class_init(RwtermioCExtensionClass *klass)
{
}

static void rwtermio_c_extension_class_finalize(RwtermioCExtensionClass *klass)
{
}

#define VAPI_TO_C_AUTOGEN
#ifdef VAPI_TO_C_AUTOGEN

#endif //VAPI_TO_C_AUTOGEN
