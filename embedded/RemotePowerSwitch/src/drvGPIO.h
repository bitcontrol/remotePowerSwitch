/**
 *  Filename:       drvGPIO.h
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Feb 12, 2016
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2016, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef DRVGPIO_H_
#define DRVGPIO_H_

#include <cfgGlobal.h>

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
 * Starts an instance of this module.
 * Starting the instance twice without stopping it in between returns an error.
 * @return \c R_SUCCESS if the instance hasn't been started already, \c R_ERROR
 * otherwise.
 */
int drvGPIO_start(void);

/**
 * Stops an instance of this module.
 * Stopping the instance twice without starting it in between returns no error.
 * @return \c R_SUCCESS in any case.
 */
int drvGPIO_stop(void);

/**
 * Sets the state of the digital output to the solid state switch.
 * @param[in] state sets the level of the output. Any value not equals to 0
 * sets the output to HIGH (3.3V), a zero value sets it to LOW (0V).
 * @return \c R_SUCCESS in any case.
 */
void drvGPIO_setOutput(BOOL state);

#ifdef __cplusplus
}
#endif

#endif // DRVGPIO_H_
