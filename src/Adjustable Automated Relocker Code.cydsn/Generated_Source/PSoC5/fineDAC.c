/*******************************************************************************
* File Name: fineDAC.c  
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
#include "fineDAC.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 fineDAC_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 fineDAC_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static fineDAC_backupStruct fineDAC_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: fineDAC_Init
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
void fineDAC_Init(void) 
{
    fineDAC_CR0 = (fineDAC_MODE_V );

    /* Set default data source */
    #if(fineDAC_DEFAULT_DATA_SRC != 0 )
        fineDAC_CR1 = (fineDAC_DEFAULT_CNTL | fineDAC_DACBUS_ENABLE) ;
    #else
        fineDAC_CR1 = (fineDAC_DEFAULT_CNTL | fineDAC_DACBUS_DISABLE) ;
    #endif /* (fineDAC_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(fineDAC_DEFAULT_STRB != 0)
        fineDAC_Strobe |= fineDAC_STRB_EN ;
    #endif/* (fineDAC_DEFAULT_STRB != 0) */

    /* Set default range */
    fineDAC_SetRange(fineDAC_DEFAULT_RANGE); 

    /* Set default speed */
    fineDAC_SetSpeed(fineDAC_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: fineDAC_Enable
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
void fineDAC_Enable(void) 
{
    fineDAC_PWRMGR |= fineDAC_ACT_PWR_EN;
    fineDAC_STBY_PWRMGR |= fineDAC_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(fineDAC_restoreVal == 1u) 
        {
             fineDAC_CR0 = fineDAC_backup.data_value;
             fineDAC_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: fineDAC_Start
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
*  fineDAC_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void fineDAC_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(fineDAC_initVar == 0u)
    { 
        fineDAC_Init();
        fineDAC_initVar = 1u;
    }

    /* Enable power to DAC */
    fineDAC_Enable();

    /* Set default value */
    fineDAC_SetValue(fineDAC_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: fineDAC_Stop
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
void fineDAC_Stop(void) 
{
    /* Disble power to DAC */
    fineDAC_PWRMGR &= (uint8)(~fineDAC_ACT_PWR_EN);
    fineDAC_STBY_PWRMGR &= (uint8)(~fineDAC_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        fineDAC_backup.data_value = fineDAC_CR0;
        fineDAC_CR0 = fineDAC_CUR_MODE_OUT_OFF;
        fineDAC_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: fineDAC_SetSpeed
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
void fineDAC_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    fineDAC_CR0 &= (uint8)(~fineDAC_HS_MASK);
    fineDAC_CR0 |=  (speed & fineDAC_HS_MASK);
}


/*******************************************************************************
* Function Name: fineDAC_SetRange
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
void fineDAC_SetRange(uint8 range) 
{
    fineDAC_CR0 &= (uint8)(~fineDAC_RANGE_MASK);      /* Clear existing mode */
    fineDAC_CR0 |= (range & fineDAC_RANGE_MASK);      /*  Set Range  */
    fineDAC_DacTrim();
}


/*******************************************************************************
* Function Name: fineDAC_SetValue
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
void fineDAC_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 fineDAC_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    fineDAC_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        fineDAC_Data = value;
        CyExitCriticalSection(fineDAC_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: fineDAC_DacTrim
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
void fineDAC_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((fineDAC_CR0 & fineDAC_RANGE_MASK) >> 2) + fineDAC_TRIM_M7_1V_RNG_OFFSET;
    fineDAC_TR = CY_GET_XTND_REG8((uint8 *)(fineDAC_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
