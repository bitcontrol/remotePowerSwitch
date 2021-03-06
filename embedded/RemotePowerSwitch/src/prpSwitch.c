/**
 *  Filename:       prpSwitch.c
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 15, 2015
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2015-2016, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#include "prpSwitch.h"

#include <stdio.h>
#include <string.h>

#include <cfgGlobal.h>
#include <cfgPlatform.h>

#include "drvGPIO.h"

//------------------------------------------------------------------------------
// Symbols and Macros
/** Cycle period of this module's handler() function in milliseconds. */
#define CYCLE_PERIOD                    CFG_CYCLE_PERIOD

//------------------------------------------------------------------------------
// Types
// todo Auto-generated instance structure
/** Instance descriptor type. */
typedef struct inst_struct
{
    /** \c TRUE if started, \c FALSE otherwise. */
    BOOL started;

    /** State of the switch. \c TRUE if on, \c FALSE otherwise.*/
    BOOL state;
} inst_t;

//------------------------------------------------------------------------------
// Constants and Variables
static inst_t sInstDscr; /**< Instance descriptor. */

//------------------------------------------------------------------------------
// Local Functions
/**
 * Initializes the variables of the instance.
 */
static void initInst(void)
{
    // todo Auto-generated function body
    memset(&sInstDscr, 0, sizeof(sInstDscr));
}

//------------------------------------------------------------------------------
// Global Functions
int prpSwitch_start(void)
{
    // todo Auto-generated function body
    CHECK_NOT_STARTED_INT(&sInstDscr, 0);

    initInst();

    sInstDscr.started = TRUE;
    return R_SUCCESS;
}

int prpSwitch_stop(void)
{
    // todo Auto-generated function body
    if (sInstDscr.started)
    {
        sInstDscr.started = FALSE;
    }
    return R_SUCCESS;
}

void prpSwitch_handler(void)
{
    CHECK_STARTED_VOID(&sInstDscr, 0);

    drvGPIO_setOutput(sInstDscr.state);
}

int prpSwitch_getState(BOOL* value)
{
    CHECK_STARTED_INT(&sInstDscr, 0);
    CHECK_POINTER_INT(value);

    *value = sInstDscr.state;
    return R_SUCCESS;
}

int prpSwitch_setState(BOOL value)
{
    CHECK_STARTED_INT(&sInstDscr, 0);
    sInstDscr.state = value;
    return R_SUCCESS;
}
