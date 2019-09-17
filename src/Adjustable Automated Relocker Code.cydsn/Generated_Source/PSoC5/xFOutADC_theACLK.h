/*******************************************************************************
* File Name: xFOutADC_theACLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_xFOutADC_theACLK_H)
#define CY_CLOCK_xFOutADC_theACLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void xFOutADC_theACLK_Start(void) ;
void xFOutADC_theACLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void xFOutADC_theACLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void xFOutADC_theACLK_StandbyPower(uint8 state) ;
void xFOutADC_theACLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 xFOutADC_theACLK_GetDividerRegister(void) ;
void xFOutADC_theACLK_SetModeRegister(uint8 modeBitMask) ;
void xFOutADC_theACLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 xFOutADC_theACLK_GetModeRegister(void) ;
void xFOutADC_theACLK_SetSourceRegister(uint8 clkSource) ;
uint8 xFOutADC_theACLK_GetSourceRegister(void) ;
#if defined(xFOutADC_theACLK__CFG3)
void xFOutADC_theACLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 xFOutADC_theACLK_GetPhaseRegister(void) ;
#endif /* defined(xFOutADC_theACLK__CFG3) */

#define xFOutADC_theACLK_Enable()                       xFOutADC_theACLK_Start()
#define xFOutADC_theACLK_Disable()                      xFOutADC_theACLK_Stop()
#define xFOutADC_theACLK_SetDivider(clkDivider)         xFOutADC_theACLK_SetDividerRegister(clkDivider, 1u)
#define xFOutADC_theACLK_SetDividerValue(clkDivider)    xFOutADC_theACLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define xFOutADC_theACLK_SetMode(clkMode)               xFOutADC_theACLK_SetModeRegister(clkMode)
#define xFOutADC_theACLK_SetSource(clkSource)           xFOutADC_theACLK_SetSourceRegister(clkSource)
#if defined(xFOutADC_theACLK__CFG3)
#define xFOutADC_theACLK_SetPhase(clkPhase)             xFOutADC_theACLK_SetPhaseRegister(clkPhase)
#define xFOutADC_theACLK_SetPhaseValue(clkPhase)        xFOutADC_theACLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(xFOutADC_theACLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define xFOutADC_theACLK_CLKEN              (* (reg8 *) xFOutADC_theACLK__PM_ACT_CFG)
#define xFOutADC_theACLK_CLKEN_PTR          ((reg8 *) xFOutADC_theACLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define xFOutADC_theACLK_CLKSTBY            (* (reg8 *) xFOutADC_theACLK__PM_STBY_CFG)
#define xFOutADC_theACLK_CLKSTBY_PTR        ((reg8 *) xFOutADC_theACLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define xFOutADC_theACLK_DIV_LSB            (* (reg8 *) xFOutADC_theACLK__CFG0)
#define xFOutADC_theACLK_DIV_LSB_PTR        ((reg8 *) xFOutADC_theACLK__CFG0)
#define xFOutADC_theACLK_DIV_PTR            ((reg16 *) xFOutADC_theACLK__CFG0)

/* Clock MSB divider configuration register. */
#define xFOutADC_theACLK_DIV_MSB            (* (reg8 *) xFOutADC_theACLK__CFG1)
#define xFOutADC_theACLK_DIV_MSB_PTR        ((reg8 *) xFOutADC_theACLK__CFG1)

/* Mode and source configuration register */
#define xFOutADC_theACLK_MOD_SRC            (* (reg8 *) xFOutADC_theACLK__CFG2)
#define xFOutADC_theACLK_MOD_SRC_PTR        ((reg8 *) xFOutADC_theACLK__CFG2)

#if defined(xFOutADC_theACLK__CFG3)
/* Analog clock phase configuration register */
#define xFOutADC_theACLK_PHASE              (* (reg8 *) xFOutADC_theACLK__CFG3)
#define xFOutADC_theACLK_PHASE_PTR          ((reg8 *) xFOutADC_theACLK__CFG3)
#endif /* defined(xFOutADC_theACLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define xFOutADC_theACLK_CLKEN_MASK         xFOutADC_theACLK__PM_ACT_MSK
#define xFOutADC_theACLK_CLKSTBY_MASK       xFOutADC_theACLK__PM_STBY_MSK

/* CFG2 field masks */
#define xFOutADC_theACLK_SRC_SEL_MSK        xFOutADC_theACLK__CFG2_SRC_SEL_MASK
#define xFOutADC_theACLK_MODE_MASK          (~(xFOutADC_theACLK_SRC_SEL_MSK))

#if defined(xFOutADC_theACLK__CFG3)
/* CFG3 phase mask */
#define xFOutADC_theACLK_PHASE_MASK         xFOutADC_theACLK__CFG3_PHASE_DLY_MASK
#endif /* defined(xFOutADC_theACLK__CFG3) */

#endif /* CY_CLOCK_xFOutADC_theACLK_H */


/* [] END OF FILE */
