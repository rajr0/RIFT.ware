
#ifndef _H_toaster
#define _H_toaster
/* 

*** Generated by yangdump 0.9.8.519M
*** Copyright (c) 2009, Netconf Central, Inc., All Rights Reserved.

    module toaster
    revision 2009-11-20

    namespace http://netconfcentral.com/ns/toaster
    organization Netconf Central

 */

#include <xmlstring.h>

#ifndef _H_dlq
#include "dlq.h"
#endif

#ifndef _H_ncxtypes
#include "ncxtypes.h"
#endif

#ifndef _H_status
#include "status.h"
#endif

#define y_toaster_M_toaster (const xmlChar *)"toaster"
#define y_toaster_R_toaster (const xmlChar *)"2009-11-20"

#define y_toaster_I_toast_type (const xmlChar *)"toast-type"
#define y_toaster_I_white_bread (const xmlChar *)"white-bread"
#define y_toaster_I_wheat_bread (const xmlChar *)"wheat-bread"
#define y_toaster_I_wonder_bread (const xmlChar *)"wonder-bread"
#define y_toaster_I_frozen_waffle (const xmlChar *)"frozen-waffle"
#define y_toaster_I_frozen_bagel (const xmlChar *)"frozen-bagel"
#define y_toaster_I_hash_brown (const xmlChar *)"hash-brown"

#define y_toaster_N_cancel_toast (const xmlChar *)"cancel-toast"
#define y_toaster_N_make_toast (const xmlChar *)"make-toast"
#define y_toaster_N_toastDone (const xmlChar *)"toastDone"
#define y_toaster_N_toastStatus (const xmlChar *)"toastStatus"
#define y_toaster_N_toaster (const xmlChar *)"toaster"
#define y_toaster_N_toasterDoneness (const xmlChar *)"toasterDoneness"
#define y_toaster_N_toasterManufacturer (const xmlChar *)"toasterManufacturer"
#define y_toaster_N_toasterModelNumber (const xmlChar *)"toasterModelNumber"
#define y_toaster_N_toasterStatus (const xmlChar *)"toasterStatus"
#define y_toaster_N_toasterToastType (const xmlChar *)"toasterToastType"

/* container /toaster */
typedef struct y_toaster_T_toaster_ {
    xmlChar *toasterManufacturer;
    xmlChar *toasterModelNumber;
    xmlChar *toasterStatus;
} y_toaster_T_toaster;

/* container /make-toast/input */
typedef struct y_toaster_T_make_toast_input_ {
    uint32 toasterDoneness;
    val_idref_t *toasterToastType;
} y_toaster_T_make_toast_input;

/* notification /toastDone */
typedef struct y_toaster_T_toastDone_ {
    xmlChar *toastStatus;
} y_toaster_T_toastDone;

/* send a y_toaster_toastDone notification */
extern void
    y_toaster_toastDone_send (
        struct ncx_instance_t_ *instance,
        const xmlChar *toastStatus);

/* toaster module init 1 */
extern status_t
    y_toaster_init (
        struct ncx_instance_t_ *instance,
        const xmlChar *modname,
        const xmlChar *revision);

/* toaster module init 2 */
extern status_t
    y_toaster_init2 (struct ncx_instance_t_ *instance);

/* toaster module cleanup */
extern void
    y_toaster_cleanup (struct ncx_instance_t_ *instance);

#endif