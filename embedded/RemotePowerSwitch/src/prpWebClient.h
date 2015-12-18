/**
 *  Filename:       prpWebClient.h
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 17, 2015
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef PRPWEBCLIENT_H_
#define PRPWEBCLIENT_H_

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
 * @param uri points to the C string that contains the URI of the web server.
 * @return \c R_SUCCESS if the instance hasn't been started already, \c R_ERROR
 * otherwise.
 */
int prpWebClient_start(const char* uri);

/**
 * Stops an instance of this module.
 * Stopping the instance twice without starting it in between returns no error.
 * @return \c R_SUCCESS in any case.
 */
int prpWebClient_stop(void);

/**
 * Todo Add Doxygen documentation; 17-Dec-2015/ais
 */
int prpWebClient_GET_switch(BOOL* value);

/**
 * Todo Add Doxygen documentation; 17-Dec-2015/ais
 */
int prpWebClient_POST_status(BOOL value);

#ifdef __cplusplus
}
#endif

#endif // PRPWEBCLIENT_H_
