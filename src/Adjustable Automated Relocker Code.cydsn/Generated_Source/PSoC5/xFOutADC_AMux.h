/*******************************************************************************
* File Name: xFOutADC_AMux.h
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

#if !defined(CY_AMUX_xFOutADC_AMux_H)
#define CY_AMUX_xFOutADC_AMux_H

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

void xFOutADC_AMux_Start(void) ;
#define xFOutADC_AMux_Init() xFOutADC_AMux_Start()
void xFOutADC_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void xFOutADC_AMux_Stop(void); */
/* void xFOutADC_AMux_Select(uint8 channel); */
/* void xFOutADC_AMux_Connect(uint8 channel); */
/* void xFOutADC_AMux_Disconnect(uint8 channel); */
/* void xFOutADC_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define xFOutADC_AMux_CHANNELS  2u
#define xFOutADC_AMux_MUXTYPE   1
#define xFOutADC_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define xFOutADC_AMux_NULL_CHANNEL 0xFFu
#define xFOutADC_AMux_MUX_SINGLE   1
#define xFOutADC_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if xFOutADC_AMux_MUXTYPE == xFOutADC_AMux_MUX_SINGLE
# if !xFOutADC_AMux_ATMOSTONE
#  define xFOutADC_AMux_Connect(channel) xFOutADC_AMux_Set(channel)
# endif
# define xFOutADC_AMux_Disconnect(channel) xFOutADC_AMux_Unset(channel)
#else
# if !xFOutADC_AMux_ATMOSTONE
void xFOutADC_AMux_Connect(uint8 channel) ;
# endif
void xFOutADC_AMux_Disconnect(uint8 channel) ;
#endif

#if xFOutADC_AMux_ATMOSTONE
# define xFOutADC_AMux_Stop() xFOutADC_AMux_DisconnectAll()
# define xFOutADC_AMux_Select(channel) xFOutADC_AMux_FastSelect(channel)
void xFOutADC_AMux_DisconnectAll(void) ;
#else
# define xFOutADC_AMux_Stop() xFOutADC_AMux_Start()
void xFOutADC_AMux_Select(uint8 channel) ;
# define xFOutADC_AMux_DisconnectAll() xFOutADC_AMux_Start()
#endif

#endif /* CY_AMUX_xFOutADC_AMux_H */


/* [] END OF FILE */
