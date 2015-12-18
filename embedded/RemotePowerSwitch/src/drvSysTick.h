/**
 *  Filename:       drvSysTick.h
 *  Platform(s):    Linux
 *  Project:
 *  Created:        Mar 26, 2013
 *  Description:    System Tick driver module.
 *
 *                  This module provides a periodic timer that can be used as
 *                  system tick generator.
 *  Notes:
 *  Author:         Andreas Isenegger
 *  Copyright:      2013-2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef DRVSYSTICK_H_
#define DRVSYSTICK_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Symbols and Macros

//------------------------------------------------------------------------------
// Types

//------------------------------------------------------------------------------
// Constants and Variables

//------------------------------------------------------------------------------
// Functions
/**
 * Starts the driver instance.
 * @param[in] instId is the instance identifier.
 * @param[in] period_us is the period of the timer in microseconds.
 * @return \c R_SUCCESS if the timer could be started, \c R_ERROR otherwise.
 */
int drvSysTick_start(int instId, unsigned int period_us);

/**
 * Stops the driver instance.
 * @param[in] instId is the instance identifier.
 * @return \c R_SUCCESS if the parameter checks pass, \c R_ERROR otherwise.
 */
int drvSysTick_stop(int instId);

/**
 * Returns the number of missed system ticks since the start of the timer. A
 * tick is being considered as missed if drvSysTick_waitForTick() hasn't
 * been called between two consecutive ticks.
 * @param[in] instId is the instance identifier.
 * @param[out] missed points to the variable that will hold the number of
 * missed system ticks since the start of the timer. In case of an error the
 * the variable won't be changed.
 * @return \c R_SUCCESS if the timer is running, \c R_ERROR otherwise.
 */
 int drvSysTick_getMissed(int instId, unsigned long long* missed);

/**
 * Returns the period of the System Tick Timer.
 * @param[in] instId is the instance identifier.
 * @param[out] period_us points to the variable that will hold the period of
 * the System Tick Timer in microseconds. In case of an error the variable
 * won't be changed.
 * @return \c R_SUCCESS if the timer is running, \c R_ERROR otherwise.
 */
 int drvSysTick_getPeriod(int instId, unsigned int* period_us);

/**
 * Returns the uptime of the driver instance.
 * If the driver instance has been started at the beginning of the application,
 * then this function returns the uptime of the application.
 * @param[in] instId is the instance identifier.
 * @param[out] uptime points to the variable that will hold the uptime of the
 * driver instance in microseconds. In case of an error the variable won't
 * be changed.
 * @return \c R_SUCCESS if the parameter checks pass, \c R_ERROR otherwise.
 */
 int drvSysTick_getUptime(int instId, unsigned long long* uptime);

 /**
 * Waits for tick of the System Tick Timer.
 * This function blocks until the System Tick Timer expires.
 * @param[in] instId is the instance identifier.
 * @return \c R_SUCCESS if the parameter checks pass, \c R_ERROR otherwise.
 */
int drvSysTick_waitForTick(int instId);

#ifdef __cplusplus
}
#endif

#endif /* DRVSYSTICK_H_ */
