/*******************************************************************************
* File Name: coarseDAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "coarseDAC.h"

static coarseDAC_backupStruct coarseDAC_backup;


/*******************************************************************************
* Function Name: coarseDAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void coarseDAC_SaveConfig(void) 
{
    if (!((coarseDAC_CR1 & coarseDAC_SRC_MASK) == coarseDAC_SRC_UDB))
    {
        coarseDAC_backup.data_value = coarseDAC_Data;
    }
}


/*******************************************************************************
* Function Name: coarseDAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void coarseDAC_RestoreConfig(void) 
{
    if (!((coarseDAC_CR1 & coarseDAC_SRC_MASK) == coarseDAC_SRC_UDB))
    {
        if((coarseDAC_Strobe & coarseDAC_STRB_MASK) == coarseDAC_STRB_EN)
        {
            coarseDAC_Strobe &= (uint8)(~coarseDAC_STRB_MASK);
            coarseDAC_Data = coarseDAC_backup.data_value;
            coarseDAC_Strobe |= coarseDAC_STRB_EN;
        }
        else
        {
            coarseDAC_Data = coarseDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: coarseDAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  coarseDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void coarseDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(coarseDAC_ACT_PWR_EN == (coarseDAC_PWRMGR & coarseDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        coarseDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        coarseDAC_backup.enableState = 0u;
    }
    
    coarseDAC_Stop();
    coarseDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: coarseDAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  coarseDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void coarseDAC_Wakeup(void) 
{
    coarseDAC_RestoreConfig();
    
    if(coarseDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        coarseDAC_Enable();

        /* Restore the data register */
        coarseDAC_SetValue(coarseDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
