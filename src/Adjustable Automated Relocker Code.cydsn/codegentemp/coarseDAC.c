/*******************************************************************************
* File Name: coarseDAC.c  
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
#include "coarseDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 coarseDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 coarseDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static coarseDAC_backupStruct coarseDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: coarseDAC_Init
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
void coarseDAC_Init(void) 
{
    coarseDAC_CR0 = (coarseDAC_MODE_V );

    /* Set default data source */
    #if(coarseDAC_DEFAULT_DATA_SRC != 0 )
        coarseDAC_CR1 = (coarseDAC_DEFAULT_CNTL | coarseDAC_DACBUS_ENABLE) ;
    #else
        coarseDAC_CR1 = (coarseDAC_DEFAULT_CNTL | coarseDAC_DACBUS_DISABLE) ;
    #endif /* (coarseDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(coarseDAC_DEFAULT_STRB != 0)
        coarseDAC_Strobe |= coarseDAC_STRB_EN ;
    #endif/* (coarseDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    coarseDAC_SetRange(coarseDAC_DEFAULT_RANGE); 

    /* Set default speed */
    coarseDAC_SetSpeed(coarseDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: coarseDAC_Enable
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
void coarseDAC_Enable(void) 
{
    coarseDAC_PWRMGR |= coarseDAC_ACT_PWR_EN;
    coarseDAC_STBY_PWRMGR |= coarseDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(coarseDAC_restoreVal == 1u) 
        {
             coarseDAC_CR0 = coarseDAC_backup.data_value;
             coarseDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: coarseDAC_Start
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
*  coarseDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void coarseDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(coarseDAC_initVar == 0u)
    { 
        coarseDAC_Init();
        coarseDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    coarseDAC_Enable();

    /* Set default value */
    coarseDAC_SetValue(coarseDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: coarseDAC_Stop
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
void coarseDAC_Stop(void) 
{
    /* Disble power to DAC */
    coarseDAC_PWRMGR &= (uint8)(~coarseDAC_ACT_PWR_EN);
    coarseDAC_STBY_PWRMGR &= (uint8)(~coarseDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        coarseDAC_backup.data_value = coarseDAC_CR0;
        coarseDAC_CR0 = coarseDAC_CUR_MODE_OUT_OFF;
        coarseDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: coarseDAC_SetSpeed
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
void coarseDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    coarseDAC_CR0 &= (uint8)(~coarseDAC_HS_MASK);
    coarseDAC_CR0 |=  (speed & coarseDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: coarseDAC_SetRange
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
void coarseDAC_SetRange(uint8 range) 
{
    coarseDAC_CR0 &= (uint8)(~coarseDAC_RANGE_MASK);      /* Clear existing mode */
    coarseDAC_CR0 |= (range & coarseDAC_RANGE_MASK);      /*  Set Range  */
    coarseDAC_DacTrim();
}


/*******************************************************************************
* Function Name: coarseDAC_SetValue
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
void coarseDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 coarseDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    coarseDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        coarseDAC_Data = value;
        CyExitCriticalSection(coarseDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: coarseDAC_DacTrim
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
void coarseDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((coarseDAC_CR0 & coarseDAC_RANGE_MASK) >> 2) + coarseDAC_TRIM_M7_1V_RNG_OFFSET;
    coarseDAC_TR = CY_GET_XTND_REG8((uint8 *)(coarseDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
