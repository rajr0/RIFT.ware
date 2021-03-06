
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
 * @file rwuagent_nb_req_xml_int.cpp
 *
 * Management agent northbound request handler for XML
 */

#include "rwuagent.hpp"
#include "rwuagent_nb_req.hpp"
#include "rwuagent_xml_mgmt_system.hpp"

using namespace rw_uagent;
using namespace rw_yang;

NbReqXmlReload::NbReqXmlReload(
    Instance* instance, XMLMgmtSystem* mgmt, std::string reload_xml)
  : NbReq(
      instance,
      "NbReqXML",
      RW_MGMTAGT_NB_REQ_TYPE_RWXML)
  , mgmt_(mgmt)
  , reload_xml_(reload_xml)
{
}

NbReqXmlReload::~NbReqXmlReload()
{
}

StartStatus NbReqXmlReload::execute()
{
  RWMEMLOG(memlog_buf_, RWMEMLOG_MEM2, "request");

  auto* sbreq = new SbReqEditConfig(instance_, this, RequestMode::XML, reload_xml_.c_str());

  return sbreq->start_xact();
}



StartStatus NbReqXmlReload::respond(
    SbReq* sbreq,
    rw_yang::XMLDocument::uptr_t rsp_dom)
{
  RWMEMLOG(memlog_buf_, RWMEMLOG_MEM2, "respond with dom",
       RWMEMLOG_ARG_PRINTF_INTPTR("sbreq=0x%" PRIX64,(intptr_t)sbreq) );

  rwsched_dispatch_async_f(instance_->rwsched_tasklet(),
                           rwsched_dispatch_get_main_queue(instance_->rwsched()),
                           mgmt_,
                           XMLMgmtSystem::reload_trx_complete_cb);

  delete this;
  return StartStatus::Done;
}

StartStatus NbReqXmlReload::respond(
    SbReq* sbreq,
    NetconfErrorList* nc_errors)
{
  RWMEMLOG(memlog_buf_, RWMEMLOG_MEM2, "respond with error",
      RWMEMLOG_ARG_PRINTF_INTPTR("sbreq=0x%" PRIX64,(intptr_t)sbreq) );

  rwsched_dispatch_async_f(instance_->rwsched_tasklet(),
                           rwsched_dispatch_get_main_queue(instance_->rwsched()),
                           mgmt_,
                           XMLMgmtSystem::reload_trx_complete_cb);

  delete this;
  return StartStatus::Done;
}

StartStatus NbReqXmlReload::respond(
    SbReq* sbreq,
    const rw_keyspec_path_t* ks,
    const ProtobufCMessage* msg )
{
  RWMEMLOG( memlog_buf_, RWMEMLOG_MEM2, "respond with keyspec and message",
        RWMEMLOG_ARG_PRINTF_INTPTR("sbreq=0x%" PRIX64,(intptr_t)sbreq) );

  rwsched_dispatch_async_f(instance_->rwsched_tasklet(),
                           rwsched_dispatch_get_main_queue(instance_->rwsched()),
                           mgmt_,
                           XMLMgmtSystem::reload_trx_complete_cb);

  delete this;
  return StartStatus::Done;
}
