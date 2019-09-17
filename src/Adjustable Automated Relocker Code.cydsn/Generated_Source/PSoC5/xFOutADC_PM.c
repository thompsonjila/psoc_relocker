/*******************************************************************************
* File Name: xFOutADC_PM.c
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

#include "xFOutADC.h"

static xFOutADC_BACKUP_STRUCT xFOutADC_backup =
{
    xFOutADC_DISABLED,
    xFOutADC_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: xFOutADC_SaveConfig
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
*  xFOutADC_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void xFOutADC_SaveConfig(void) 
{
    xFOutADC_backup.deccr = xFOutADC_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: xFOutADC_RestoreConfig
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
*  xFOutADC_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void xFOutADC_RestoreConfig(void) 
{
    xFOutADC_DEC_CR_REG = xFOutADC_backup.deccr;
}


/*******************************************************************************
* Function Name: xFOutADC_Sleep
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
*  xFOutADC_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void xFOutADC_Sleep(void) 
{
    /* Save ADC enable state */
    if((xFOutADC_ACT_PWR_DEC_EN == (xFOutADC_PWRMGR_DEC_REG & xFOutADC_ACT_PWR_DEC_EN)) &&
       (xFOutADC_ACT_PWR_DSM_EN == (xFOutADC_PWRMGR_DSM_REG & xFOutADC_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        xFOutADC_backup.enableState = xFOutADC_ENABLED;
        if((xFOutADC_DEC_CR_REG & xFOutADC_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            xFOutADC_backup.enableState |= xFOutADC_STARTED;
        }
		
        /* Stop the configuration */
        xFOutADC_Stop();
    }
    else
    {
        /* Component is disabled */
        xFOutADC_backup.enableState = xFOutADC_DISABLED;
    }

    /* Save the user configuration */
    xFOutADC_SaveConfig();
}


/*******************************************************************************
* Function Name: xFOutADC_Wakeup
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
*  xFOutADC_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void xFOutADC_Wakeup(void) 
{
    /* Restore the configuration */
    xFOutADC_RestoreConfig();

    /* Enables the component operation */
    if(xFOutADC_backup.enableState != xFOutADC_DISABLED)
    {
        xFOutADC_Enable();
        if((xFOutADC_backup.enableState & xFOutADC_STARTED) != 0u)
        {
            xFOutADC_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
