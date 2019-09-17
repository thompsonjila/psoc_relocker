/*******************************************************************************
* File Name: greenLight.h  
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

#if !defined(CY_PINS_greenLight_H) /* Pins greenLight_H */
#define CY_PINS_greenLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "greenLight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 greenLight__PORT == 15 && ((greenLight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    greenLight_Write(uint8 value);
void    greenLight_SetDriveMode(uint8 mode);
uint8   greenLight_ReadDataReg(void);
uint8   greenLight_Read(void);
void    greenLight_SetInterruptMode(uint16 position, uint16 mode);
uint8   greenLight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the greenLight_SetDriveMode() function.
     *  @{
     */
        #define greenLight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define greenLight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define greenLight_DM_RES_UP          PIN_DM_RES_UP
        #define greenLight_DM_RES_DWN         PIN_DM_RES_DWN
        #define greenLight_DM_OD_LO           PIN_DM_OD_LO
        #define greenLight_DM_OD_HI           PIN_DM_OD_HI
        #define greenLight_DM_STRONG          PIN_DM_STRONG
        #define greenLight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define greenLight_MASK               greenLight__MASK
#define greenLight_SHIFT              greenLight__SHIFT
#define greenLight_WIDTH              1u

/* Interrupt constants */
#if defined(greenLight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in greenLight_SetInterruptMode() function.
     *  @{
     */
        #define greenLight_INTR_NONE      (uint16)(0x0000u)
        #define greenLight_INTR_RISING    (uint16)(0x0001u)
        #define greenLight_INTR_FALLING   (uint16)(0x0002u)
        #define greenLight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define greenLight_INTR_MASK      (0x01u) 
#endif /* (greenLight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define greenLight_PS                     (* (reg8 *) greenLight__PS)
/* Data Register */
#define greenLight_DR                     (* (reg8 *) greenLight__DR)
/* Port Number */
#define greenLight_PRT_NUM                (* (reg8 *) greenLight__PRT) 
/* Connect to Analog Globals */                                                  
#define greenLight_AG                     (* (reg8 *) greenLight__AG)                       
/* Analog MUX bux enable */
#define greenLight_AMUX                   (* (reg8 *) greenLight__AMUX) 
/* Bidirectional Enable */                                                        
#define greenLight_BIE                    (* (reg8 *) greenLight__BIE)
/* Bit-mask for Aliased Register Access */
#define greenLight_BIT_MASK               (* (reg8 *) greenLight__BIT_MASK)
/* Bypass Enable */
#define greenLight_BYP                    (* (reg8 *) greenLight__BYP)
/* Port wide control signals */                                                   
#define greenLight_CTL                    (* (reg8 *) greenLight__CTL)
/* Drive Modes */
#define greenLight_DM0                    (* (reg8 *) greenLight__DM0) 
#define greenLight_DM1                    (* (reg8 *) greenLight__DM1)
#define greenLight_DM2                    (* (reg8 *) greenLight__DM2) 
/* Input Buffer Disable Override */
#define greenLight_INP_DIS                (* (reg8 *) greenLight__INP_DIS)
/* LCD Common or Segment Drive */
#define greenLight_LCD_COM_SEG            (* (reg8 *) greenLight__LCD_COM_SEG)
/* Enable Segment LCD */
#define greenLight_LCD_EN                 (* (reg8 *) greenLight__LCD_EN)
/* Slew Rate Control */
#define greenLight_SLW                    (* (reg8 *) greenLight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define greenLight_PRTDSI__CAPS_SEL       (* (reg8 *) greenLight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define greenLight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) greenLight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define greenLight_PRTDSI__OE_SEL0        (* (reg8 *) greenLight__PRTDSI__OE_SEL0) 
#define greenLight_PRTDSI__OE_SEL1        (* (reg8 *) greenLight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define greenLight_PRTDSI__OUT_SEL0       (* (reg8 *) greenLight__PRTDSI__OUT_SEL0) 
#define greenLight_PRTDSI__OUT_SEL1       (* (reg8 *) greenLight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define greenLight_PRTDSI__SYNC_OUT       (* (reg8 *) greenLight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(greenLight__SIO_CFG)
    #define greenLight_SIO_HYST_EN        (* (reg8 *) greenLight__SIO_HYST_EN)
    #define greenLight_SIO_REG_HIFREQ     (* (reg8 *) greenLight__SIO_REG_HIFREQ)
    #define greenLight_SIO_CFG            (* (reg8 *) greenLight__SIO_CFG)
    #define greenLight_SIO_DIFF           (* (reg8 *) greenLight__SIO_DIFF)
#endif /* (greenLight__SIO_CFG) */

/* Interrupt Registers */
#if defined(greenLight__INTSTAT)
    #define greenLight_INTSTAT            (* (reg8 *) greenLight__INTSTAT)
    #define greenLight_SNAP               (* (reg8 *) greenLight__SNAP)
    
	#define greenLight_0_INTTYPE_REG 		(* (reg8 *) greenLight__0__INTTYPE)
#endif /* (greenLight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_greenLight_H */


/* [] END OF FILE */
