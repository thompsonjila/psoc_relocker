/*******************************************************************************
* File Name: eMonADC_PM.c
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

#include "eMonADC.h"


/***************************************
* Local data allocation
***************************************/

static eMonADC_BACKUP_STRUCT  eMonADC_backup =
{
    eMonADC_DISABLED
};


/*******************************************************************************
* Function Name: eMonADC_SaveConfig
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
void eMonADC_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: eMonADC_RestoreConfig
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
void eMonADC_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: eMonADC_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The eMonADC_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  eMonADC_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void eMonADC_Sleep(void)
{
    if((eMonADC_PWRMGR_SAR_REG  & eMonADC_ACT_PWR_SAR_EN) != 0u)
    {
        if((eMonADC_SAR_CSR0_REG & eMonADC_SAR_SOF_START_CONV) != 0u)
        {
            eMonADC_backup.enableState = eMonADC_ENABLED | eMonADC_STARTED;
        }
        else
        {
            eMonADC_backup.enableState = eMonADC_ENABLED;
        }
        eMonADC_Stop();
    }
    else
    {
        eMonADC_backup.enableState = eMonADC_DISABLED;
    }
}


/*******************************************************************************
* Function Name: eMonADC_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  eMonADC_Sleep() was called. If the component was enabled before the
*  eMonADC_Sleep() function was called, the
*  eMonADC_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  eMonADC_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void eMonADC_Wakeup(void)
{
    if(eMonADC_backup.enableState != eMonADC_DISABLED)
    {
        eMonADC_Enable();
        #if(eMonADC_DEFAULT_CONV_MODE != eMonADC__HARDWARE_TRIGGER)
            if((eMonADC_backup.enableState & eMonADC_STARTED) != 0u)
            {
                eMonADC_StartConvert();
            }
        #endif /* End eMonADC_DEFAULT_CONV_MODE != eMonADC__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */
