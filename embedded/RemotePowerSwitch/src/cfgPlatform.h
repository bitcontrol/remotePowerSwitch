
/**
 *  Filename:       cfgPlatform.h
 *  Platform(s):    Linux
 *  Project:
 *  Created:        Feb 4, 2013
 *  Description:    Platform configuration module.
 *  Notes:
 *  Author:         Andreas Isenegger
 *  Copyright:      2013-2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#ifndef CFGPLATFORM_H_
#define CFGPLATFORM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cfgProject.h"

//------------------------------------------------------------------------------
// Symbols and Macros
/*
 * If the PRINT_ macros haven't been defined on project level (inside
 * cfgProject.h), then they are defined here.
 */
#ifndef PRINT_DEBUG
#define PRINT_DEBUG(...) \
    printf("+++ DEBUG +++: Func %s, file %s, line %i:\n", \
        __func__, __FILE__, __LINE__); \
    printf(__VA_ARGS__); \
    printf("\n");
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR(...) \
    printf("+++ ERROR +++: Func %s, file %s, line %i:\n", \
        __func__, __FILE__, __LINE__); \
    printf(__VA_ARGS__); \
    printf("\n");
#endif

#ifndef PRINT_WARNG
#define PRINT_WARNG(...) \
    printf("+++ WARNG +++: Func %s, file %s, line %i:\n", \
        __func__, __FILE__, __LINE__); \
    printf(__VA_ARGS__); \
    printf("\n");
#endif

//------------------------------------------------------------------------------
// Types
enum
{
    CFG_DRVSYSTICK_INST_N0,
    CFG_DRVSYSTICK_INST_CNT,
};

enum
{
    CFG_DRVTIME_INST_N0,
    CFG_DRVTIME_INST_CNT,
};

enum
{
    DRV_PERITIMER_INST_N0,
    DRV_PERITIMER_INST_CNT,
};

enum
{
    CFG_DRVUART_INST_N0,
    CFG_DRVUART_INST_N1,
    CFG_DRVUART_INST_N2,
    CFG_DRVUART_INST_N3,
    CFG_DRVUART_INST_N4,
    CFG_DRVUART_INST_N5,
    CFG_DRVUART_INST_N6,
    CFG_DRVUART_INST_N7,
    CFG_DRVUART_INST_N8,
    CFG_DRVUART_INST_N9,
    CFG_DRVUART_INST_N10,
    CFG_DRVUART_INST_N11,
    CFG_DRVUART_INST_N12,
    CFG_DRVUART_INST_N13,
    CFG_DRVUART_INST_N14,
    CFG_DRVUART_INST_N15,
    CFG_DRVUART_INST_N16,
    CFG_DRVUART_INST_N17,
    CFG_DRVUART_INST_N18,
    CFG_DRVUART_INST_N19,
    CFG_DRVUART_INST_N20,
    CFG_DRVUART_INST_N21,
    CFG_DRVUART_INST_N22,
    CFG_DRVUART_INST_N23,
    CFG_DRVUART_INST_CNT,
};

//------------------------------------------------------------------------------
// Constants and Variables

//------------------------------------------------------------------------------
// Functions

#ifdef __cplusplus
}
#endif

#endif /* CFGPLATFORM_H_ */
