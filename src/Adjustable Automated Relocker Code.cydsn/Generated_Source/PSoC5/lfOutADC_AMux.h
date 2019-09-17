/*******************************************************************************
* File Name: LFOutADC_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_LFOutADC_AMux_H)
#define CY_AMUX_LFOutADC_AMux_H

#include "cyfitter.h"
#include "cyfitter_cfg.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
         (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))    
    #include "cytypes.h"
#else
    #include "syslib/cy_syslib.h"
#endif /* ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) */


/***************************************
*        Function Prototypes
***************************************/

void LFOutADC_AMux_Start(void) ;
#define LFOutADC_AMux_Init() LFOutADC_AMux_Start()
void LFOutADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void LFOutADC_AMux_Stop(void); */
/* void LFOutADC_AMux_Select(uint8 channel); */
/* void LFOutADC_AMux_Connect(uint8 channel); */
/* void LFOutADC_AMux_Disconnect(uint8 channel); */
/* void LFOutADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define LFOutADC_AMux_CHANNELS  2u
#define LFOutADC_AMux_MUXTYPE   1
#define LFOutADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define LFOutADC_AMux_NULL_CHANNEL 0xFFu
#define LFOutADC_AMux_MUX_SINGLE   1
#define LFOutADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if LFOutADC_AMux_MUXTYPE == LFOutADC_AMux_MUX_SINGLE
# if !LFOutADC_AMux_ATMOSTONE
#  define LFOutADC_AMux_Connect(channel) LFOutADC_AMux_Set(channel)
# endif
# define LFOutADC_AMux_Disconnect(channel) LFOutADC_AMux_Unset(channel)
#else
# if !LFOutADC_AMux_ATMOSTONE
void LFOutADC_AMux_Connect(uint8 channel) ;
# endif
void LFOutADC_AMux_Disconnect(uint8 channel) ;
#endif

#if LFOutADC_AMux_ATMOSTONE
# define LFOutADC_AMux_Stop() LFOutADC_AMux_DisconnectAll()
# define LFOutADC_AMux_Select(channel) LFOutADC_AMux_FastSelect(channel)
void LFOutADC_AMux_DisconnectAll(void) ;
#else
# define LFOutADC_AMux_Stop() LFOutADC_AMux_Start()
void LFOutADC_AMux_Select(uint8 channel) ;
# define LFOutADC_AMux_DisconnectAll() LFOutADC_AMux_Start()
#endif

#endif /* CY_AMUX_LFOutADC_AMux_H */


/* [] END OF FILE */
