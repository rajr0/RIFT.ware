/*COPYRIGHT**
    Copyright (C) 2005-2014 Intel Corporation.  All Rights Reserved.

    This file is part of SEP Development Kit

    SEP Development Kit is free software; you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    SEP Development Kit is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SEP Development Kit; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, you may use this file as part of a free software
    library without restriction.  Specifically, if other files instantiate
    templates or use macros or inline functions from this file, or you compile
    this file and link it with other files to produce an executable, this
    file does not by itself cause the resulting executable to be covered by
    the GNU General Public License.  This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
**COPYRIGHT*/

#ifndef _HASWELL_SERVER_IRP_H_INC_
#define _HASWELL_SERVER_IRP_H_INC_

#define HASWELL_SERVER_IRP_DID            0x2F34 // IRP PerfMon DID --- B:D 0:5:6

#define IRP_COUNTER_UNIT_CONTROL_OFFSET    0xf4
#define IRP_COUNTER_0_CONTROL_OFFSET       0xd8
#define IRP_COUNTER_1_CONTROL_OFFSET       0xdc
#define IRP_COUNTER_2_CONTROL_OFFSET       0xe0
#define IRP_COUNTER_3_CONTROL_OFFSET       0xe8

#define ENABLE_HASWELL_SERVER_IRP_COUNTERS    0x400000
#define DISABLE_HASWELL_SERVER_IRP_COUNTERS   0x100

extern DISPATCH_NODE                        haswell_server_irp_dispatch;

#endif
