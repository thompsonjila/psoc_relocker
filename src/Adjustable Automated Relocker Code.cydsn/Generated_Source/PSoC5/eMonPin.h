/*******************************************************************************
* File Name: eMonPin.h  
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

#if !defined(CY_PINS_eMonPin_H) /* Pins eMonPin_H */
#define CY_PINS_eMonPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "eMonPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 eMonPin__PORT == 15 && ((eMonPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    eMonPin_Write(uint8 value);
void    eMonPin_SetDriveMode(uint8 mode);
uint8   eMonPin_ReadDataReg(void);
uint8   eMonPin_Read(void);
void    eMonPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   eMonPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the eMonPin_SetDriveMode() function.
     *  @{
     */
        #define eMonPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define eMonPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define eMonPin_DM_RES_UP          PIN_DM_RES_UP
        #define eMonPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define eMonPin_DM_OD_LO           PIN_DM_OD_LO
        #define eMonPin_DM_OD_HI           PIN_DM_OD_HI
        #define eMonPin_DM_STRONG          PIN_DM_STRONG
        #define eMonPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define eMonPin_MASK               eMonPin__MASK
#define eMonPin_SHIFT              eMonPin__SHIFT
#define eMonPin_WIDTH              1u

/* Interrupt constants */
#if defined(eMonPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in eMonPin_SetInterruptMode() function.
     *  @{
     */
        #define eMonPin_INTR_NONE      (uint16)(0x0000u)
        #define eMonPin_INTR_RISING    (uint16)(0x0001u)
        #define eMonPin_INTR_FALLING   (uint16)(0x0002u)
        #define eMonPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define eMonPin_INTR_MASK      (0x01u) 
#endif /* (eMonPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define eMonPin_PS                     (* (reg8 *) eMonPin__PS)
/* Data Register */
#define eMonPin_DR                     (* (reg8 *) eMonPin__DR)
/* Port Number */
#define eMonPin_PRT_NUM                (* (reg8 *) eMonPin__PRT) 
/* Connect to Analog Globals */                                                  
#define eMonPin_AG                     (* (reg8 *) eMonPin__AG)                       
/* Analog MUX bux enable */
#define eMonPin_AMUX                   (* (reg8 *) eMonPin__AMUX) 
/* Bidirectional Enable */                                                        
#define eMonPin_BIE                    (* (reg8 *) eMonPin__BIE)
/* Bit-mask for Aliased Register Access */
#define eMonPin_BIT_MASK               (* (reg8 *) eMonPin__BIT_MASK)
/* Bypass Enable */
#define eMonPin_BYP                    (* (reg8 *) eMonPin__BYP)
/* Port wide control signals */                                                   
#define eMonPin_CTL                    (* (reg8 *) eMonPin__CTL)
/* Drive Modes */
#define eMonPin_DM0                    (* (reg8 *) eMonPin__DM0) 
#define eMonPin_DM1                    (* (reg8 *) eMonPin__DM1)
#define eMonPin_DM2                    (* (reg8 *) eMonPin__DM2) 
/* Input Buffer Disable Override */
#define eMonPin_INP_DIS                (* (reg8 *) eMonPin__INP_DIS)
/* LCD Common or Segment Drive */
#define eMonPin_LCD_COM_SEG            (* (reg8 *) eMonPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define eMonPin_LCD_EN                 (* (reg8 *) eMonPin__LCD_EN)
/* Slew Rate Control */
#define eMonPin_SLW                    (* (reg8 *) eMonPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define eMonPin_PRTDSI__CAPS_SEL       (* (reg8 *) eMonPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define eMonPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) eMonPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define eMonPin_PRTDSI__OE_SEL0        (* (reg8 *) eMonPin__PRTDSI__OE_SEL0) 
#define eMonPin_PRTDSI__OE_SEL1        (* (reg8 *) eMonPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define eMonPin_PRTDSI__OUT_SEL0       (* (reg8 *) eMonPin__PRTDSI__OUT_SEL0) 
#define eMonPin_PRTDSI__OUT_SEL1       (* (reg8 *) eMonPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define eMonPin_PRTDSI__SYNC_OUT       (* (reg8 *) eMonPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(eMonPin__SIO_CFG)
    #define eMonPin_SIO_HYST_EN        (* (reg8 *) eMonPin__SIO_HYST_EN)
    #define eMonPin_SIO_REG_HIFREQ     (* (reg8 *) eMonPin__SIO_REG_HIFREQ)
    #define eMonPin_SIO_CFG            (* (reg8 *) eMonPin__SIO_CFG)
    #define eMonPin_SIO_DIFF           (* (reg8 *) eMonPin__SIO_DIFF)
#endif /* (eMonPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(eMonPin__INTSTAT)
    #define eMonPin_INTSTAT            (* (reg8 *) eMonPin__INTSTAT)
    #define eMonPin_SNAP               (* (reg8 *) eMonPin__SNAP)
    
	#define eMonPin_0_INTTYPE_REG 		(* (reg8 *) eMonPin__0__INTTYPE)
#endif /* (eMonPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_eMonPin_H */


/* [] END OF FILE */
