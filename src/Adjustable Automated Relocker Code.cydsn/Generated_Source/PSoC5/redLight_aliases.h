/*******************************************************************************
* File Name: redLight.h  
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

#if !defined(CY_PINS_redLight_ALIASES_H) /* Pins redLight_ALIASES_H */
#define CY_PINS_redLight_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define redLight_0			(redLight__0__PC)
#define redLight_0_INTR	((uint16)((uint16)0x0001u << redLight__0__SHIFT))

#define redLight_INTR_ALL	 ((uint16)(redLight_0_INTR))

#endif /* End Pins redLight_ALIASES_H */


/* [] END OF FILE */
