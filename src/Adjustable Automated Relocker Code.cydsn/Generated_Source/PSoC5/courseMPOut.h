/*******************************************************************************
* File Name: courseMPOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_courseMPOut_H) /* Pins courseMPOut_H */
#define CY_PINS_courseMPOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "courseMPOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 courseMPOut__PORT == 15 && ((courseMPOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    courseMPOut_Write(uint8 value);
void    courseMPOut_SetDriveMode(uint8 mode);
uint8   courseMPOut_ReadDataReg(void);
uint8   courseMPOut_Read(void);
void    courseMPOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   courseMPOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the courseMPOut_SetDriveMode() function.
     *  @{
     */
        #define courseMPOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define courseMPOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define courseMPOut_DM_RES_UP          PIN_DM_RES_UP
        #define courseMPOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define courseMPOut_DM_OD_LO           PIN_DM_OD_LO
        #define courseMPOut_DM_OD_HI           PIN_DM_OD_HI
        #define courseMPOut_DM_STRONG          PIN_DM_STRONG
        #define courseMPOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define courseMPOut_MASK               courseMPOut__MASK
#define courseMPOut_SHIFT              courseMPOut__SHIFT
#define courseMPOut_WIDTH              1u

/* Interrupt constants */
#if defined(courseMPOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in courseMPOut_SetInterruptMode() function.
     *  @{
     */
        #define courseMPOut_INTR_NONE      (uint16)(0x0000u)
        #define courseMPOut_INTR_RISING    (uint16)(0x0001u)
        #define courseMPOut_INTR_FALLING   (uint16)(0x0002u)
        #define courseMPOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define courseMPOut_INTR_MASK      (0x01u) 
#endif /* (courseMPOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define courseMPOut_PS                     (* (reg8 *) courseMPOut__PS)
/* Data Register */
#define courseMPOut_DR                     (* (reg8 *) courseMPOut__DR)
/* Port Number */
#define courseMPOut_PRT_NUM                (* (reg8 *) courseMPOut__PRT) 
/* Connect to Analog Globals */                                                  
#define courseMPOut_AG                     (* (reg8 *) courseMPOut__AG)                       
/* Analog MUX bux enable */
#define courseMPOut_AMUX                   (* (reg8 *) courseMPOut__AMUX) 
/* Bidirectional Enable */                                                        
#define courseMPOut_BIE                    (* (reg8 *) courseMPOut__BIE)
/* Bit-mask for Aliased Register Access */
#define courseMPOut_BIT_MASK               (* (reg8 *) courseMPOut__BIT_MASK)
/* Bypass Enable */
#define courseMPOut_BYP                    (* (reg8 *) courseMPOut__BYP)
/* Port wide control signals */                                                   
#define courseMPOut_CTL                    (* (reg8 *) courseMPOut__CTL)
/* Drive Modes */
#define courseMPOut_DM0                    (* (reg8 *) courseMPOut__DM0) 
#define courseMPOut_DM1                    (* (reg8 *) courseMPOut__DM1)
#define courseMPOut_DM2                    (* (reg8 *) courseMPOut__DM2) 
/* Input Buffer Disable Override */
#define courseMPOut_INP_DIS                (* (reg8 *) courseMPOut__INP_DIS)
/* LCD Common or Segment Drive */
#define courseMPOut_LCD_COM_SEG            (* (reg8 *) courseMPOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define courseMPOut_LCD_EN                 (* (reg8 *) courseMPOut__LCD_EN)
/* Slew Rate Control */
#define courseMPOut_SLW                    (* (reg8 *) courseMPOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define courseMPOut_PRTDSI__CAPS_SEL       (* (reg8 *) courseMPOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define courseMPOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) courseMPOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define courseMPOut_PRTDSI__OE_SEL0        (* (reg8 *) courseMPOut__PRTDSI__OE_SEL0) 
#define courseMPOut_PRTDSI__OE_SEL1        (* (reg8 *) courseMPOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define courseMPOut_PRTDSI__OUT_SEL0       (* (reg8 *) courseMPOut__PRTDSI__OUT_SEL0) 
#define courseMPOut_PRTDSI__OUT_SEL1       (* (reg8 *) courseMPOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define courseMPOut_PRTDSI__SYNC_OUT       (* (reg8 *) courseMPOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(courseMPOut__SIO_CFG)
    #define courseMPOut_SIO_HYST_EN        (* (reg8 *) courseMPOut__SIO_HYST_EN)
    #define courseMPOut_SIO_REG_HIFREQ     (* (reg8 *) courseMPOut__SIO_REG_HIFREQ)
    #define courseMPOut_SIO_CFG            (* (reg8 *) courseMPOut__SIO_CFG)
    #define courseMPOut_SIO_DIFF           (* (reg8 *) courseMPOut__SIO_DIFF)
#endif /* (courseMPOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(courseMPOut__INTSTAT)
    #define courseMPOut_INTSTAT            (* (reg8 *) courseMPOut__INTSTAT)
    #define courseMPOut_SNAP               (* (reg8 *) courseMPOut__SNAP)
    
	#define courseMPOut_0_INTTYPE_REG 		(* (reg8 *) courseMPOut__0__INTTYPE)
#endif /* (courseMPOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_courseMPOut_H */


/* [] END OF FILE */
