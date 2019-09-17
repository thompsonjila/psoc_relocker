/*******************************************************************************
* File Name: fineDAC_PM.c  
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

#include "fineDAC.h"

static fineDAC_backupStruct fineDAC_backup;


/*******************************************************************************
* Function Name: fineDAC_SaveConfig
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
void fineDAC_SaveConfig(void) 
{
    if (!((fineDAC_CR1 & fineDAC_SRC_MASK) == fineDAC_SRC_UDB))
    {
        fineDAC_backup.data_value = fineDAC_Data;
    }
}


/*******************************************************************************
* Function Name: fineDAC_RestoreConfig
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
void fineDAC_RestoreConfig(void) 
{
    if (!((fineDAC_CR1 & fineDAC_SRC_MASK) == fineDAC_SRC_UDB))
    {
        if((fineDAC_Strobe & fineDAC_STRB_MASK) == fineDAC_STRB_EN)
        {
            fineDAC_Strobe &= (uint8)(~fineDAC_STRB_MASK);
            fineDAC_Data = fineDAC_backup.data_value;
            fineDAC_Strobe |= fineDAC_STRB_EN;
        }
        else
        {
            fineDAC_Data = fineDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: fineDAC_Sleep
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
*  fineDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void fineDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(fineDAC_ACT_PWR_EN == (fineDAC_PWRMGR & fineDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        fineDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        fineDAC_backup.enableState = 0u;
    }
    
    fineDAC_Stop();
    fineDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: fineDAC_Wakeup
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
*  fineDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void fineDAC_Wakeup(void) 
{
    fineDAC_RestoreConfig();
    
    if(fineDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        fineDAC_Enable();

        /* Restore the data register */
        fineDAC_SetValue(fineDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
