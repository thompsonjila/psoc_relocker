/*******************************************************************************
* File Name: fOpAmp_PM.c
* Version 1.90
*
* Description:
*  This file provides the power management source code to the API for the 
*  OpAmp (Analog Buffer) component.
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

static fOpAmp_BACKUP_STRUCT  fOpAmp_backup;


/*******************************************************************************  
* Function Name: fOpAmp_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration registers.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
*******************************************************************************/
void fOpAmp_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: fOpAmp_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration registers.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void fOpAmp_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: fOpAmp_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  fOpAmp_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void fOpAmp_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((fOpAmp_PM_ACT_CFG_REG & fOpAmp_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        fOpAmp_backup.enableState = 1u;
         /* Stops the component */
         fOpAmp_Stop();
    }
    else
    {
        /* Component is disabled */
        fOpAmp_backup.enableState = 0u;
    }
    /* Saves the configuration */
    fOpAmp_SaveConfig();
}


/*******************************************************************************  
* Function Name: fOpAmp_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  fOpAmp_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void fOpAmp_Wakeup(void) 
{
    /* Restore the user configuration */
    fOpAmp_RestoreConfig();

    /* Enables the component operation */
    if(fOpAmp_backup.enableState == 1u)
    {
        fOpAmp_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
