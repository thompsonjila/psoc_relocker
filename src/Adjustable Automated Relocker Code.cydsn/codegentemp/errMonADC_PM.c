/*******************************************************************************
* File Name: errMonADC_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "errMonADC.h"


/***************************************
* Local data allocation
***************************************/

static errMonADC_BACKUP_STRUCT  errMonADC_backup =
{
    errMonADC_DISABLED
};


/*******************************************************************************
* Function Name: errMonADC_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void errMonADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: errMonADC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void errMonADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: errMonADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The errMonADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  errMonADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void errMonADC_Sleep(void)
{
    if((errMonADC_PWRMGR_SAR_REG  & errMonADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((errMonADC_SAR_CSR0_REG & errMonADC_SAR_SOF_START_CONV) != 0u)
        {
            errMonADC_backup.enableState = errMonADC_ENABLED | errMonADC_STARTED;
        }
        else
        {
            errMonADC_backup.enableState = errMonADC_ENABLED;
        }
        errMonADC_Stop();
    }
    else
    {
        errMonADC_backup.enableState = errMonADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: errMonADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  errMonADC_Sleep() was called. If the component was enabled before the
*  errMonADC_Sleep() function was called, the
*  errMonADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  errMonADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void errMonADC_Wakeup(void)
{
    if(errMonADC_backup.enableState != errMonADC_DISABLED)
    {
        errMonADC_Enable();
        #if(errMonADC_DEFAULT_CONV_MODE != errMonADC__HARDWARE_TRIGGER)
            if((errMonADC_backup.enableState & errMonADC_STARTED) != 0u)
            {
                errMonADC_StartConvert();
            }
        #endif /* End errMonADC_DEFAULT_CONV_MODE != errMonADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
