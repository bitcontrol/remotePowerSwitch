/**
 *  Filename:       main.c
 *  Platform(s):    Linux
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 15, 2015
 *  Description:    Remote Power Switch
 *                  This application has the following tasks:
 *                  - Periodically read the desired switch status from the Internet
 *                  - Update the digital output to the power switch according to
 *                    the desired switch status
 *                  - Periodically write the actual switch status to the Internet
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2015-2016 Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include <cfgGlobal.h>
#include <cfgPlatform.h>

#include "drvGPIO.h"
#include "drvSysTick.h"
#include "prpSwitch.h"
#include "prpWebClient.h"

//------------------------------------------------------------------------------
// Symbols and Macros

//------------------------------------------------------------------------------
// Types

//------------------------------------------------------------------------------
// Constants and Variables

//------------------------------------------------------------------------------
// Local Functions

//------------------------------------------------------------------------------
// Global Functions
int main(int argc, char *argv[])
{
    BOOL cmd; // On/off command from web server; FALSE means off, TRUE means on

    /* Check command line arguments. */
    if (argc == 2)
    {
        printf("The argument supplied is %s\n", argv[1]);
    } else if (argc > 2)
    {
        printf("Too many arguments supplied.");
        return EXIT_FAILURE;
    } else
    {
        printf("Argument 'URI of web server' expected. Example: "
                "http://localhost:9000/");
        return EXIT_FAILURE;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    /* Start driver modules. */
    drvSysTick_start(CFG_DRVSYSTICK_INST_N0, CFG_CYCLE_PERIOD * 1000); // [us]
    drvGPIO_start();

    /* Start data preparation modules. */
    prpSwitch_start();
    prpWebClient_start(argv[1]);

    /* Main application loop. */
    while (TRUE) {
        drvSysTick_waitForTick(CFG_DRVSYSTICK_INST_N0);

        cmd = FALSE; // For safety
        prpWebClient_GET_switch(&cmd);
        prpSwitch_setState(cmd);
        prpSwitch_handler();
        prpWebClient_POST_status(cmd);

        puts("Main loop triggered."); // Todo Can be deleted
    }

    /* Stop data preparation modules. */
    prpWebClient_stop();
    prpSwitch_stop();

    /* Stop driver modules. */
    drvGPIO_stop();
    drvSysTick_stop(CFG_DRVSYSTICK_INST_N0);

    curl_global_cleanup();

    return EXIT_SUCCESS;
}
