/**
 *  Filename:       drvGPIO.c
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Feb 12, 2016
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2016, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#include "drvGPIO.h"

#include <stdio.h>
#include <string.h>

#include <cfgGlobal.h>
#include <cfgPlatform.h>

#include <bcm2835.h>

//------------------------------------------------------------------------------
// Symbols and Macros
/** Cycle period of this module's handler() function in milliseconds. */
#define CYCLE_PERIOD                    CFG_CYCLE_PERIOD

// RPi Plug P1 pin 11 (which is BCM2836 GPIO pin 17)
#define PIN RPI_V2_GPIO_P1_11

//------------------------------------------------------------------------------
// Types
/** Instance descriptor type. */
typedef struct inst_struct
{
    /** \c TRUE if started, \c FALSE otherwise. */
    BOOL started;
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
    memset(&sInstDscr, 0, sizeof(sInstDscr));
}

//------------------------------------------------------------------------------
// Global Functions
int drvGPIO_start(void)
{
    int retVal;

    CHECK_NOT_STARTED_INT(&sInstDscr, 0);

    initInst();
    retVal = bcm2835_init();
    if (retVal)
    {
        // Set the pin to be an output
        bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_set_pad(BCM2835_PAD_GROUP_GPIO_0_27,
                BCM2835_PAD_DRIVE_10mA);

        sInstDscr.started = TRUE;
        return R_SUCCESS;
    }
    else {
        PRINT_ERROR("bcm2835_init() returned %i", retVal);
    }
    return R_ERROR;
}

int drvGPIO_stop(void)
{
    if (sInstDscr.started)
    {
        bcm2835_close();
        sInstDscr.started = FALSE;
    }
    return R_SUCCESS;
}

void drvGPIO_setOutput(BOOL state)
{
    bcm2835_gpio_write(PIN, state ? HIGH : LOW);
}
