/*******************************************************************************
* File Name: courseDAC_PM.c  
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

#include "courseDAC.h"

static courseDAC_backupStruct courseDAC_backup;


/*******************************************************************************
* Function Name: courseDAC_SaveConfig
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
void courseDAC_SaveConfig(void) 
{
    if (!((courseDAC_CR1 & courseDAC_SRC_MASK) == courseDAC_SRC_UDB))
    {
        courseDAC_backup.data_value = courseDAC_Data;
    }
}


/*******************************************************************************
* Function Name: courseDAC_RestoreConfig
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
void courseDAC_RestoreConfig(void) 
{
    if (!((courseDAC_CR1 & courseDAC_SRC_MASK) == courseDAC_SRC_UDB))
    {
        if((courseDAC_Strobe & courseDAC_STRB_MASK) == courseDAC_STRB_EN)
        {
            courseDAC_Strobe &= (uint8)(~courseDAC_STRB_MASK);
            courseDAC_Data = courseDAC_backup.data_value;
            courseDAC_Strobe |= courseDAC_STRB_EN;
        }
        else
        {
            courseDAC_Data = courseDAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: courseDAC_Sleep
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
*  courseDAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void courseDAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(courseDAC_ACT_PWR_EN == (courseDAC_PWRMGR & courseDAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        courseDAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        courseDAC_backup.enableState = 0u;
    }
    
    courseDAC_Stop();
    courseDAC_SaveConfig();
}


/*******************************************************************************
* Function Name: courseDAC_Wakeup
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
*  courseDAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void courseDAC_Wakeup(void) 
{
    courseDAC_RestoreConfig();
    
    if(courseDAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        courseDAC_Enable();

        /* Restore the data register */
        courseDAC_SetValue(courseDAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
