/*******************************************************************************
* File Name: orangeLight.h  
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

#if !defined(CY_PINS_orangeLight_ALIASES_H) /* Pins orangeLight_ALIASES_H */
#define CY_PINS_orangeLight_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define orangeLight_0			(orangeLight__0__PC)
#define orangeLight_0_INTR	((uint16)((uint16)0x0001u << orangeLight__0__SHIFT))

#define orangeLight_INTR_ALL	 ((uint16)(orangeLight_0_INTR))

#endif /* End Pins orangeLight_ALIASES_H */


/* [] END OF FILE */
