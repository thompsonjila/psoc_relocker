/*******************************************************************************
* File Name: cOpAmp_PM.c
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

#include "cOpAmp.h"

static cOpAmp_BACKUP_STRUCT  cOpAmp_backup;


/*******************************************************************************  
* Function Name: cOpAmp_SaveConfig
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
void cOpAmp_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: cOpAmp_RestoreConfig
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
void cOpAmp_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: cOpAmp_Sleep
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
*  cOpAmp_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void cOpAmp_Sleep(void) 
{
    /* Save OpAmp enable state */
    if((cOpAmp_PM_ACT_CFG_REG & cOpAmp_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        cOpAmp_backup.enableState = 1u;
         /* Stops the component */
         cOpAmp_Stop();
    }
    else
    {
        /* Component is disabled */
        cOpAmp_backup.enableState = 0u;
    }
    /* Saves the configuration */
    cOpAmp_SaveConfig();
}


/*******************************************************************************  
* Function Name: cOpAmp_Wakeup
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
*  cOpAmp_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void cOpAmp_Wakeup(void) 
{
    /* Restore the user configuration */
    cOpAmp_RestoreConfig();

    /* Enables the component operation */
    if(cOpAmp_backup.enableState == 1u)
    {
        cOpAmp_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
