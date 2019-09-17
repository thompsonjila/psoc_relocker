/*******************************************************************************
* File Name: pin_triggerMode.h  
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

#if !defined(CY_PINS_pin_triggerMode_H) /* Pins pin_triggerMode_H */
#define CY_PINS_pin_triggerMode_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "pin_triggerMode_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 pin_triggerMode__PORT == 15 && ((pin_triggerMode__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    pin_triggerMode_Write(uint8 value);
void    pin_triggerMode_SetDriveMode(uint8 mode);
uint8   pin_triggerMode_ReadDataReg(void);
uint8   pin_triggerMode_Read(void);
void    pin_triggerMode_SetInterruptMode(uint16 position, uint16 mode);
uint8   pin_triggerMode_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the pin_triggerMode_SetDriveMode() function.
     *  @{
     */
        #define pin_triggerMode_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define pin_triggerMode_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define pin_triggerMode_DM_RES_UP          PIN_DM_RES_UP
        #define pin_triggerMode_DM_RES_DWN         PIN_DM_RES_DWN
        #define pin_triggerMode_DM_OD_LO           PIN_DM_OD_LO
        #define pin_triggerMode_DM_OD_HI           PIN_DM_OD_HI
        #define pin_triggerMode_DM_STRONG          PIN_DM_STRONG
        #define pin_triggerMode_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define pin_triggerMode_MASK               pin_triggerMode__MASK
#define pin_triggerMode_SHIFT              pin_triggerMode__SHIFT
#define pin_triggerMode_WIDTH              1u

/* Interrupt constants */
#if defined(pin_triggerMode__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pin_triggerMode_SetInterruptMode() function.
     *  @{
     */
        #define pin_triggerMode_INTR_NONE      (uint16)(0x0000u)
        #define pin_triggerMode_INTR_RISING    (uint16)(0x0001u)
        #define pin_triggerMode_INTR_FALLING   (uint16)(0x0002u)
        #define pin_triggerMode_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define pin_triggerMode_INTR_MASK      (0x01u) 
#endif /* (pin_triggerMode__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define pin_triggerMode_PS                     (* (reg8 *) pin_triggerMode__PS)
/* Data Register */
#define pin_triggerMode_DR                     (* (reg8 *) pin_triggerMode__DR)
/* Port Number */
#define pin_triggerMode_PRT_NUM                (* (reg8 *) pin_triggerMode__PRT) 
/* Connect to Analog Globals */                                                  
#define pin_triggerMode_AG                     (* (reg8 *) pin_triggerMode__AG)                       
/* Analog MUX bux enable */
#define pin_triggerMode_AMUX                   (* (reg8 *) pin_triggerMode__AMUX) 
/* Bidirectional Enable */                                                        
#define pin_triggerMode_BIE                    (* (reg8 *) pin_triggerMode__BIE)
/* Bit-mask for Aliased Register Access */
#define pin_triggerMode_BIT_MASK               (* (reg8 *) pin_triggerMode__BIT_MASK)
/* Bypass Enable */
#define pin_triggerMode_BYP                    (* (reg8 *) pin_triggerMode__BYP)
/* Port wide control signals */                                                   
#define pin_triggerMode_CTL                    (* (reg8 *) pin_triggerMode__CTL)
/* Drive Modes */
#define pin_triggerMode_DM0                    (* (reg8 *) pin_triggerMode__DM0) 
#define pin_triggerMode_DM1                    (* (reg8 *) pin_triggerMode__DM1)
#define pin_triggerMode_DM2                    (* (reg8 *) pin_triggerMode__DM2) 
/* Input Buffer Disable Override */
#define pin_triggerMode_INP_DIS                (* (reg8 *) pin_triggerMode__INP_DIS)
/* LCD Common or Segment Drive */
#define pin_triggerMode_LCD_COM_SEG            (* (reg8 *) pin_triggerMode__LCD_COM_SEG)
/* Enable Segment LCD */
#define pin_triggerMode_LCD_EN                 (* (reg8 *) pin_triggerMode__LCD_EN)
/* Slew Rate Control */
#define pin_triggerMode_SLW                    (* (reg8 *) pin_triggerMode__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define pin_triggerMode_PRTDSI__CAPS_SEL       (* (reg8 *) pin_triggerMode__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define pin_triggerMode_PRTDSI__DBL_SYNC_IN    (* (reg8 *) pin_triggerMode__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define pin_triggerMode_PRTDSI__OE_SEL0        (* (reg8 *) pin_triggerMode__PRTDSI__OE_SEL0) 
#define pin_triggerMode_PRTDSI__OE_SEL1        (* (reg8 *) pin_triggerMode__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define pin_triggerMode_PRTDSI__OUT_SEL0       (* (reg8 *) pin_triggerMode__PRTDSI__OUT_SEL0) 
#define pin_triggerMode_PRTDSI__OUT_SEL1       (* (reg8 *) pin_triggerMode__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define pin_triggerMode_PRTDSI__SYNC_OUT       (* (reg8 *) pin_triggerMode__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(pin_triggerMode__SIO_CFG)
    #define pin_triggerMode_SIO_HYST_EN        (* (reg8 *) pin_triggerMode__SIO_HYST_EN)
    #define pin_triggerMode_SIO_REG_HIFREQ     (* (reg8 *) pin_triggerMode__SIO_REG_HIFREQ)
    #define pin_triggerMode_SIO_CFG            (* (reg8 *) pin_triggerMode__SIO_CFG)
    #define pin_triggerMode_SIO_DIFF           (* (reg8 *) pin_triggerMode__SIO_DIFF)
#endif /* (pin_triggerMode__SIO_CFG) */

/* Interrupt Registers */
#if defined(pin_triggerMode__INTSTAT)
    #define pin_triggerMode_INTSTAT            (* (reg8 *) pin_triggerMode__INTSTAT)
    #define pin_triggerMode_SNAP               (* (reg8 *) pin_triggerMode__SNAP)
    
	#define pin_triggerMode_0_INTTYPE_REG 		(* (reg8 *) pin_triggerMode__0__INTTYPE)
#endif /* (pin_triggerMode__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_pin_triggerMode_H */


/* [] END OF FILE */
