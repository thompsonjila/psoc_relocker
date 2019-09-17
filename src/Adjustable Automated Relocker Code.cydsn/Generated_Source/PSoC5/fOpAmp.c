/*******************************************************************************
* File Name: fOpAmp.c
* Version 1.90
*
* Description:
*  This file provides the source code to the API for OpAmp (Analog Buffer) 
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "fOpAmp.h"

uint8 fOpAmp_initVar = 0u;


/*******************************************************************************   
* Function Name: fOpAmp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  fOpAmp_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void fOpAmp_Init(void) 
{
    fOpAmp_SetPower(fOpAmp_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: fOpAmp_Enable
********************************************************************************
*
* Summary:
*  Enables the OpAmp block operation
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void fOpAmp_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    fOpAmp_PUMP_CR1_REG  |= (fOpAmp_PUMP_CR1_CLKSEL | fOpAmp_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    fOpAmp_PM_ACT_CFG_REG |= fOpAmp_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    fOpAmp_PM_STBY_CFG_REG |= fOpAmp_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   fOpAmp_Start
********************************************************************************
*
* Summary:
*  The start function initializes the Analog Buffer with the default values and 
*  sets the power to the given level. A power level of 0, is same as 
*  executing the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  fOpAmp_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void fOpAmp_Start(void) 
{
    if(fOpAmp_initVar == 0u)
    {
        fOpAmp_initVar = 1u;
        fOpAmp_Init();
    }

    fOpAmp_Enable();
}


/*******************************************************************************
* Function Name: fOpAmp_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void fOpAmp_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    fOpAmp_PM_ACT_CFG_REG &= (uint8)(~fOpAmp_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    fOpAmp_PM_STBY_CFG_REG &= (uint8)(~fOpAmp_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(fOpAmp_PM_ACT_CFG_REG == 0u)
    {
        fOpAmp_PUMP_CR1_REG &= (uint8)(~(fOpAmp_PUMP_CR1_CLKSEL | fOpAmp_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: fOpAmp_SetPower
********************************************************************************
*
* Summary:
*  Sets power level of Analog buffer.
*
* Parameters: 
*  power: PSoC3: Sets power level between low (1) and high power (3).
*         PSoC5: Sets power level High (0)
*
* Return:
*  void
*
**********************************************************************************/
void fOpAmp_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        fOpAmp_CR_REG &= (uint8)(~fOpAmp_PWR_MASK);
        fOpAmp_CR_REG |= power & fOpAmp_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(fOpAmp_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
