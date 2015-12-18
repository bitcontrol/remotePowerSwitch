/**
 *  Filename:       drvSysTick.c
 *  Platform(s):    Linux
 *  Project:
 *  Created:        Mar 26, 2013
 *  Description:    System Tick driver module.
 *  Notes:
 *  Author:         Andreas Isenegger
 *  Copyright:      2013-2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#include "drvSysTick.h"

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <cfgGlobal.h>
#include <cfgPlatform.h>

//------------------------------------------------------------------------------
// Symbols and Macros

//------------------------------------------------------------------------------
// Types
/** Instance descriptor type. */
typedef struct inst_struct
{
    int fileDscr; /**< File descriptor. */
    unsigned long long missed; /**< Number of ticks missed since the start. */
    unsigned int period_us; /**< Period of the timer in microseconds. */
    BOOL started; /**< \c TRUE if instance started, \c FALSE otherwise. */
} inst_t;

//------------------------------------------------------------------------------
// Constants and Variables
static inst_t sInstDscr[CFG_DRVSYSTICK_INST_CNT]; /**< Instance descriptor. */

//------------------------------------------------------------------------------
// Local Functions
/**
 * Initializes the variables of the driver instance.
 * @param[in] instId is the instance identifier.
 */
static void initInst(int instId)
{
    memset(&sInstDscr[instId], 0, sizeof(sInstDscr[instId]));
}

//------------------------------------------------------------------------------
// Global Functions
int drvSysTick_start(int instId, unsigned int period_us)
{
    int fd;
    struct itimerspec itval;
    unsigned int ns;
    unsigned int sec;

    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);
    CHECK_NOT_STARTED_INT(sInstDscr, instId);

    if (period_us > 0 && period_us <= 1000000)
    {
        initInst(instId);

        /* Create the timer. */
        fd = timerfd_create(CLOCK_MONOTONIC, 0);
        if (fd >= 0)
        {
            sInstDscr[instId].missed = 0;
            sInstDscr[instId].fileDscr = fd;

            /* Make the timer periodic. */
            sec = period_us / 1000000;
            ns = (period_us - (sec * 1000000)) * 1000;
            itval.it_interval.tv_sec = sec;
            itval.it_interval.tv_nsec = ns;
            itval.it_value.tv_sec = sec;
            itval.it_value.tv_nsec = ns;
            if (timerfd_settime(fd, 0, &itval, NULL ) >= 0)
            {
                sInstDscr[instId].period_us = period_us;
                sInstDscr[instId].started = TRUE;
                return R_SUCCESS;
            }
            else
            {
                PRINT_ERROR("[%i]: timerfd_settime() failed", instId);
            }
        }
        else
        {
            PRINT_ERROR("[%i]: timerfd_create() failed", instId);
        }
    }
    else
    {
        PRINT_ERROR("[%i]: period_us outside range: %u", instId, period_us);
    }
    return R_ERROR;
}

int drvSysTick_stop(int instId)
{
    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);

    if (sInstDscr[instId].started)
    {
        sInstDscr[instId].started = FALSE;
    }
    return R_SUCCESS;
}

int drvSysTick_getMissed(int instId, unsigned long long* missed)
{
    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);
    CHECK_STARTED_INT(sInstDscr, instId);
    CHECK_POINTER_INT(missed);

    *missed = sInstDscr[instId].missed;
    return R_SUCCESS;
}

int drvSysTick_getPeriod(int instId, unsigned int* period_us)
{
    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);
    CHECK_STARTED_INT(sInstDscr, instId);
    CHECK_POINTER_INT(period_us);

    *period_us = sInstDscr[instId].period_us;
    return R_SUCCESS;
}

int drvSysTick_getUptime(int instId, unsigned long long* uptime)
{
    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);
    CHECK_STARTED_INT(sInstDscr, instId);
    CHECK_POINTER_INT(uptime);

// todo Add implementation; 09-Apr-2013/ais
//     DISABLE_INTERRUPTS();
//     *uptime = sInstDscr[instId].uptime;
//     ENABLE_INTERRUPTS();
    return R_SUCCESS;
}

int drvSysTick_waitForTick(int instId)
{
    unsigned long long missed;

    CHECK_RANGE_INT(instId, 0, CFG_DRVSYSTICK_INST_CNT);
    CHECK_STARTED_INT(sInstDscr, instId);

    /* Wait for the next timer event. If we have missed any the number is
     * written to "missed". */
    if (read(sInstDscr[instId].fileDscr, &missed, sizeof(missed)) >= 0)
    {
        if (missed > 0) // Should always be >= 1, but check it anyway
        {
            sInstDscr[instId].missed += missed - 1;
        }
        return R_SUCCESS;
    }
    else
    {
        PRINT_ERROR("[%i]: Timer %i couldn't be read",
            instId, sInstDscr[instId].fileDscr);
    }
    return R_ERROR;
}
