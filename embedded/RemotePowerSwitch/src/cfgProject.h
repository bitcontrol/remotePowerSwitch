/**
 *  Filename:       cfgProject.h
 *  Platform(s):    Linux
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 15, 2015
 *  Description:    Remote Power Switch
 *  Notes:
 *  Author:         Andreas Isenegger
 *  Copyright:      2015-2016 Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef CFGPROJECT_H_
#define CFGPROJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Symbols and Macros
/*
 * If project specific implementations of the PRINT_... macros are required,
 * define them here. If not, they have got a default implementation in
 * \c cfgPlatform.h.
 */
// #define PRINT_DEBUG(...)                printf(__VA_ARGS__)
// #define PRINT_ERROR(...)                printf(__VA_ARGS__)
// #define PRINT_WARNG(...)                printf(__VA_ARGS__)

/** Time of the long application cycle in milliseconds. */
#define CFG_CYCLE_PERIOD_LONG           (10 * CFG_CYCLE_PERIOD_SHORT)

/**
  * Time of the short application cycle in milliseconds.
  * Dependency of other modules for precise time calculations:
  * 1000 divided by this number should result in an integer number (remainder
  * equals to zero).
  */
#define CFG_CYCLE_PERIOD_SHORT          100

//------------------------------------------------------------------------------
// Types

//------------------------------------------------------------------------------
// Constants and Variables

//------------------------------------------------------------------------------
// Functions

#ifdef __cplusplus
}
#endif

#endif // CFGPROJECT_H_
