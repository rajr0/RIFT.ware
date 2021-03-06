
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
 * @file rwvx.h
 * @author Tim Mortsolf (tim.mortsolf@riftio.com)
 * @date 05/12/2014
 * @brief Top level API include for rwvx submodule
 */

#ifndef __RWVX_H__
#define __RWVX_H__

#include <rwvcs_zk_api.h>
#include <rwlib.h>
#include <rwlog.h>
#include <rwsched.h>
#include <rwtrace.h>

#include "rw-manifest.pb-c.h"

__BEGIN_DECLS

// forward declare due to cyclic dep
typedef struct rwvcs_instance_s * rwvcs_instance_ptr_t;


#define RWVX_GET_ZK_MODULE(t_rwvx) ((t_rwvx)->rwvcs_zk_module)
struct rwvx_instance_s {
  CFRuntimeBase _base;
  // rwtrace_ctx_ptr_t rwtrace;
  rwtrace_ctx_t *rwtrace;
  rwlog_ctx_t *rwlog;
  rwsched_instance_ptr_t rwsched;
  rwsched_tasklet_ptr_t rwsched_tasklet;
  rwvcs_instance_ptr_t rwvcs;
 // rwcal_module_ptr_t rwcal_module;
  rwvcs_zk_module_ptr_t rwvcs_zk_module;
  struct rwmain_gi* rwmain;
  struct {
    int fd;
    rwsched_CFSocketRef cfsocket;
    rwsched_CFRunLoopSourceRef cfsource;
  } pacemaker_inotify;
};

RW_TYPE_DECL(rwvx_instance);
RW_CF_TYPE_EXTERN(rwvx_instance_ptr_t);

/*
 * Create a rwvx instance
 */
rwvx_instance_t * rwvx_instance_alloc();

/*
 * Free a rwvx instance
 */
void rwvx_instance_free(rwvx_instance_t * rwvx);

__END_DECLS

#endif // __RWVX_H__
