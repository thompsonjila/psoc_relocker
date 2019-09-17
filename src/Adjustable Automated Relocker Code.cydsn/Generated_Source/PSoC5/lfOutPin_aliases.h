/*******************************************************************************
* File Name: LFOutPin.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LFOutPin_ALIASES_H) /* Pins LFOutPin_ALIASES_H */
#define CY_PINS_LFOutPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define LFOutPin_0			(LFOutPin__0__PC)
#define LFOutPin_0_INTR	((uint16)((uint16)0x0001u << LFOutPin__0__SHIFT))

#define LFOutPin_INTR_ALL	 ((uint16)(LFOutPin_0_INTR))

#endif /* End Pins LFOutPin_ALIASES_H */


/* [] END OF FILE */
