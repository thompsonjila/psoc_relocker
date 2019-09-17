/*******************************************************************************
* File Name: xFOutADC_Ext_CP_Clk.h
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

#if !defined(CY_CLOCK_xFOutADC_Ext_CP_Clk_H)
#define CY_CLOCK_xFOutADC_Ext_CP_Clk_H

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

void xFOutADC_Ext_CP_Clk_Start(void) ;
void xFOutADC_Ext_CP_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void xFOutADC_Ext_CP_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void xFOutADC_Ext_CP_Clk_StandbyPower(uint8 state) ;
void xFOutADC_Ext_CP_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 xFOutADC_Ext_CP_Clk_GetDividerRegister(void) ;
void xFOutADC_Ext_CP_Clk_SetModeRegister(uint8 modeBitMask) ;
void xFOutADC_Ext_CP_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 xFOutADC_Ext_CP_Clk_GetModeRegister(void) ;
void xFOutADC_Ext_CP_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 xFOutADC_Ext_CP_Clk_GetSourceRegister(void) ;
#if defined(xFOutADC_Ext_CP_Clk__CFG3)
void xFOutADC_Ext_CP_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 xFOutADC_Ext_CP_Clk_GetPhaseRegister(void) ;
#endif /* defined(xFOutADC_Ext_CP_Clk__CFG3) */

#define xFOutADC_Ext_CP_Clk_Enable()                       xFOutADC_Ext_CP_Clk_Start()
#define xFOutADC_Ext_CP_Clk_Disable()                      xFOutADC_Ext_CP_Clk_Stop()
#define xFOutADC_Ext_CP_Clk_SetDivider(clkDivider)         xFOutADC_Ext_CP_Clk_SetDividerRegister(clkDivider, 1u)
#define xFOutADC_Ext_CP_Clk_SetDividerValue(clkDivider)    xFOutADC_Ext_CP_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define xFOutADC_Ext_CP_Clk_SetMode(clkMode)               xFOutADC_Ext_CP_Clk_SetModeRegister(clkMode)
#define xFOutADC_Ext_CP_Clk_SetSource(clkSource)           xFOutADC_Ext_CP_Clk_SetSourceRegister(clkSource)
#if defined(xFOutADC_Ext_CP_Clk__CFG3)
#define xFOutADC_Ext_CP_Clk_SetPhase(clkPhase)             xFOutADC_Ext_CP_Clk_SetPhaseRegister(clkPhase)
#define xFOutADC_Ext_CP_Clk_SetPhaseValue(clkPhase)        xFOutADC_Ext_CP_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(xFOutADC_Ext_CP_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define xFOutADC_Ext_CP_Clk_CLKEN              (* (reg8 *) xFOutADC_Ext_CP_Clk__PM_ACT_CFG)
#define xFOutADC_Ext_CP_Clk_CLKEN_PTR          ((reg8 *) xFOutADC_Ext_CP_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define xFOutADC_Ext_CP_Clk_CLKSTBY            (* (reg8 *) xFOutADC_Ext_CP_Clk__PM_STBY_CFG)
#define xFOutADC_Ext_CP_Clk_CLKSTBY_PTR        ((reg8 *) xFOutADC_Ext_CP_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define xFOutADC_Ext_CP_Clk_DIV_LSB            (* (reg8 *) xFOutADC_Ext_CP_Clk__CFG0)
#define xFOutADC_Ext_CP_Clk_DIV_LSB_PTR        ((reg8 *) xFOutADC_Ext_CP_Clk__CFG0)
#define xFOutADC_Ext_CP_Clk_DIV_PTR            ((reg16 *) xFOutADC_Ext_CP_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define xFOutADC_Ext_CP_Clk_DIV_MSB            (* (reg8 *) xFOutADC_Ext_CP_Clk__CFG1)
#define xFOutADC_Ext_CP_Clk_DIV_MSB_PTR        ((reg8 *) xFOutADC_Ext_CP_Clk__CFG1)

/* Mode and source configuration register */
#define xFOutADC_Ext_CP_Clk_MOD_SRC            (* (reg8 *) xFOutADC_Ext_CP_Clk__CFG2)
#define xFOutADC_Ext_CP_Clk_MOD_SRC_PTR        ((reg8 *) xFOutADC_Ext_CP_Clk__CFG2)

#if defined(xFOutADC_Ext_CP_Clk__CFG3)
/* Analog clock phase configuration register */
#define xFOutADC_Ext_CP_Clk_PHASE              (* (reg8 *) xFOutADC_Ext_CP_Clk__CFG3)
#define xFOutADC_Ext_CP_Clk_PHASE_PTR          ((reg8 *) xFOutADC_Ext_CP_Clk__CFG3)
#endif /* defined(xFOutADC_Ext_CP_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define xFOutADC_Ext_CP_Clk_CLKEN_MASK         xFOutADC_Ext_CP_Clk__PM_ACT_MSK
#define xFOutADC_Ext_CP_Clk_CLKSTBY_MASK       xFOutADC_Ext_CP_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define xFOutADC_Ext_CP_Clk_SRC_SEL_MSK        xFOutADC_Ext_CP_Clk__CFG2_SRC_SEL_MASK
#define xFOutADC_Ext_CP_Clk_MODE_MASK          (~(xFOutADC_Ext_CP_Clk_SRC_SEL_MSK))

#if defined(xFOutADC_Ext_CP_Clk__CFG3)
/* CFG3 phase mask */
#define xFOutADC_Ext_CP_Clk_PHASE_MASK         xFOutADC_Ext_CP_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(xFOutADC_Ext_CP_Clk__CFG3) */

#endif /* CY_CLOCK_xFOutADC_Ext_CP_Clk_H */


/* [] END OF FILE */
