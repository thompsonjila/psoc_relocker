/*******************************************************************************
* File Name: LFOutADC_PM.c
* Version 3.30
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LFOutADC.h"

static LFOutADC_BACKUP_STRUCT LFOutADC_backup =
{
    LFOutADC_DISABLED,
    LFOutADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: LFOutADC_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LFOutADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void LFOutADC_SaveConfig(void) 
{
    LFOutADC_backup.deccr = LFOutADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: LFOutADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LFOutADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void LFOutADC_RestoreConfig(void) 
{
    LFOutADC_DEC_CR_REG = LFOutADC_backup.deccr;
}


/*******************************************************************************
* Function Name: LFOutADC_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LFOutADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void LFOutADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((LFOutADC_ACT_PWR_DEC_EN == (LFOutADC_PWRMGR_DEC_REG & LFOutADC_ACT_PWR_DEC_EN)) &&
       (LFOutADC_ACT_PWR_DSM_EN == (LFOutADC_PWRMGR_DSM_REG & LFOutADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        LFOutADC_backup.enableState = LFOutADC_ENABLED;
        if((LFOutADC_DEC_CR_REG & LFOutADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            LFOutADC_backup.enableState |= LFOutADC_STARTED;
        }
		
        /* Stop the configuration */
        LFOutADC_Stop();
    }
    else
    {
        /* Component is disabled */
        LFOutADC_backup.enableState = LFOutADC_DISABLED;
    }

    /* Save the user configuration */
    LFOutADC_SaveConfig();
}


/*******************************************************************************
* Function Name: LFOutADC_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  LFOutADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void LFOutADC_Wakeup(void) 
{
    /* Restore the configuration */
    LFOutADC_RestoreConfig();

    /* Enables the component operation */
    if(LFOutADC_backup.enableState != LFOutADC_DISABLED)
    {
        LFOutADC_Enable();
        if((LFOutADC_backup.enableState & LFOutADC_STARTED) != 0u)
        {
            LFOutADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
