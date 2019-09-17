/*******************************************************************************
* File Name: courseDAC.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "courseDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 courseDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 courseDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static courseDAC_backupStruct courseDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: courseDAC_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_Init(void) 
{
    courseDAC_CR0 = (courseDAC_MODE_V );

    /* Set default data source */
    #if(courseDAC_DEFAULT_DATA_SRC != 0 )
        courseDAC_CR1 = (courseDAC_DEFAULT_CNTL | courseDAC_DACBUS_ENABLE) ;
    #else
        courseDAC_CR1 = (courseDAC_DEFAULT_CNTL | courseDAC_DACBUS_DISABLE) ;
    #endif /* (courseDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(courseDAC_DEFAULT_STRB != 0)
        courseDAC_Strobe |= courseDAC_STRB_EN ;
    #endif/* (courseDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    courseDAC_SetRange(courseDAC_DEFAULT_RANGE); 

    /* Set default speed */
    courseDAC_SetSpeed(courseDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: courseDAC_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_Enable(void) 
{
    courseDAC_PWRMGR |= courseDAC_ACT_PWR_EN;
    courseDAC_STBY_PWRMGR |= courseDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(courseDAC_restoreVal == 1u) 
        {
             courseDAC_CR0 = courseDAC_backup.data_value;
             courseDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: courseDAC_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  courseDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void courseDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(courseDAC_initVar == 0u)
    { 
        courseDAC_Init();
        courseDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    courseDAC_Enable();

    /* Set default value */
    courseDAC_SetValue(courseDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: courseDAC_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_Stop(void) 
{
    /* Disble power to DAC */
    courseDAC_PWRMGR &= (uint8)(~courseDAC_ACT_PWR_EN);
    courseDAC_STBY_PWRMGR &= (uint8)(~courseDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        courseDAC_backup.data_value = courseDAC_CR0;
        courseDAC_CR0 = courseDAC_CUR_MODE_OUT_OFF;
        courseDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: courseDAC_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    courseDAC_CR0 &= (uint8)(~courseDAC_HS_MASK);
    courseDAC_CR0 |=  (speed & courseDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: courseDAC_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_SetRange(uint8 range) 
{
    courseDAC_CR0 &= (uint8)(~courseDAC_RANGE_MASK);      /* Clear existing mode */
    courseDAC_CR0 |= (range & courseDAC_RANGE_MASK);      /*  Set Range  */
    courseDAC_DacTrim();
}


/*******************************************************************************
* Function Name: courseDAC_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 courseDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    courseDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        courseDAC_Data = value;
        CyExitCriticalSection(courseDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: courseDAC_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void courseDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((courseDAC_CR0 & courseDAC_RANGE_MASK) >> 2) + courseDAC_TRIM_M7_1V_RNG_OFFSET;
    courseDAC_TR = CY_GET_XTND_REG8((uint8 *)(courseDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
