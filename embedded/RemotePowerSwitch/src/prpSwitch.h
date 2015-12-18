/**
 *  Filename:       prpSwitch.h
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 15, 2015
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef PRPSWITCH_H_
#define PRPSWITCH_H_

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
int prpSwitch_start(void);

/**
 * Stops an instance of this module.
 * Stopping the instance twice without starting it in between returns no error.
 * @return \c R_SUCCESS in any case.
 */
int prpSwitch_stop(void);

/**
 * Handles the periodic tasks of an instance of this module.
 */
void prpSwitch_handler(void);

/**
 * Todo Add Doxygen documentation; 15-Dec-2015/ais
 */
int prpSwitch_getState(BOOL* value);

/**
 * Todo Add Doxygen documentation; 15-Dec-2015/ais
 */
int prpSwitch_setState(BOOL value);

#ifdef __cplusplus
}
#endif

#endif // PRPSWITCH_H_
