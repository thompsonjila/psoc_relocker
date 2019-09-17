/*******************************************************************************
* File Name: cOpAmp.c
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

#include "cOpAmp.h"

uint8 cOpAmp_initVar = 0u;


/*******************************************************************************   
* Function Name: cOpAmp_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  cOpAmp_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void cOpAmp_Init(void) 
{
    cOpAmp_SetPower(cOpAmp_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: cOpAmp_Enable
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
void cOpAmp_Enable(void) 
{
    /* Enable negative charge pumps in ANIF */
    cOpAmp_PUMP_CR1_REG  |= (cOpAmp_PUMP_CR1_CLKSEL | cOpAmp_PUMP_CR1_FORCE);

    /* Enable power to buffer in active mode */
    cOpAmp_PM_ACT_CFG_REG |= cOpAmp_ACT_PWR_EN;

    /* Enable power to buffer in alternative active mode */
    cOpAmp_PM_STBY_CFG_REG |= cOpAmp_STBY_PWR_EN;
}


/*******************************************************************************
* Function Name:   cOpAmp_Start
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
*  cOpAmp_initVar: Used to check the initial configuration, modified 
*  when this function is called for the first time.
*
*******************************************************************************/
void cOpAmp_Start(void) 
{
    if(cOpAmp_initVar == 0u)
    {
        cOpAmp_initVar = 1u;
        cOpAmp_Init();
    }

    cOpAmp_Enable();
}


/*******************************************************************************
* Function Name: cOpAmp_Stop
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
void cOpAmp_Stop(void) 
{
    /* Disable power to buffer in active mode template */
    cOpAmp_PM_ACT_CFG_REG &= (uint8)(~cOpAmp_ACT_PWR_EN);

    /* Disable power to buffer in alternative active mode template */
    cOpAmp_PM_STBY_CFG_REG &= (uint8)(~cOpAmp_STBY_PWR_EN);
    
    /* Disable negative charge pumps for ANIF only if all ABuf is turned OFF */
    if(cOpAmp_PM_ACT_CFG_REG == 0u)
    {
        cOpAmp_PUMP_CR1_REG &= (uint8)(~(cOpAmp_PUMP_CR1_CLKSEL | cOpAmp_PUMP_CR1_FORCE));
    }
}


/*******************************************************************************
* Function Name: cOpAmp_SetPower
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
void cOpAmp_SetPower(uint8 power) 
{
    #if (CY_PSOC3 || CY_PSOC5LP)
        cOpAmp_CR_REG &= (uint8)(~cOpAmp_PWR_MASK);
        cOpAmp_CR_REG |= power & cOpAmp_PWR_MASK;      /* Set device power */
    #else
        CYASSERT(cOpAmp_HIGHPOWER == power);
    #endif /* CY_PSOC3 || CY_PSOC5LP */
}


/* [] END OF FILE */
