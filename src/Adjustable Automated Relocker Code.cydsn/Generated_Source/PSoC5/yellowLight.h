/*******************************************************************************
* File Name: yellowLight.h  
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

#if !defined(CY_PINS_yellowLight_H) /* Pins yellowLight_H */
#define CY_PINS_yellowLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "yellowLight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 yellowLight__PORT == 15 && ((yellowLight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    yellowLight_Write(uint8 value);
void    yellowLight_SetDriveMode(uint8 mode);
uint8   yellowLight_ReadDataReg(void);
uint8   yellowLight_Read(void);
void    yellowLight_SetInterruptMode(uint16 position, uint16 mode);
uint8   yellowLight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the yellowLight_SetDriveMode() function.
     *  @{
     */
        #define yellowLight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define yellowLight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define yellowLight_DM_RES_UP          PIN_DM_RES_UP
        #define yellowLight_DM_RES_DWN         PIN_DM_RES_DWN
        #define yellowLight_DM_OD_LO           PIN_DM_OD_LO
        #define yellowLight_DM_OD_HI           PIN_DM_OD_HI
        #define yellowLight_DM_STRONG          PIN_DM_STRONG
        #define yellowLight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define yellowLight_MASK               yellowLight__MASK
#define yellowLight_SHIFT              yellowLight__SHIFT
#define yellowLight_WIDTH              1u

/* Interrupt constants */
#if defined(yellowLight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in yellowLight_SetInterruptMode() function.
     *  @{
     */
        #define yellowLight_INTR_NONE      (uint16)(0x0000u)
        #define yellowLight_INTR_RISING    (uint16)(0x0001u)
        #define yellowLight_INTR_FALLING   (uint16)(0x0002u)
        #define yellowLight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define yellowLight_INTR_MASK      (0x01u) 
#endif /* (yellowLight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define yellowLight_PS                     (* (reg8 *) yellowLight__PS)
/* Data Register */
#define yellowLight_DR                     (* (reg8 *) yellowLight__DR)
/* Port Number */
#define yellowLight_PRT_NUM                (* (reg8 *) yellowLight__PRT) 
/* Connect to Analog Globals */                                                  
#define yellowLight_AG                     (* (reg8 *) yellowLight__AG)                       
/* Analog MUX bux enable */
#define yellowLight_AMUX                   (* (reg8 *) yellowLight__AMUX) 
/* Bidirectional Enable */                                                        
#define yellowLight_BIE                    (* (reg8 *) yellowLight__BIE)
/* Bit-mask for Aliased Register Access */
#define yellowLight_BIT_MASK               (* (reg8 *) yellowLight__BIT_MASK)
/* Bypass Enable */
#define yellowLight_BYP                    (* (reg8 *) yellowLight__BYP)
/* Port wide control signals */                                                   
#define yellowLight_CTL                    (* (reg8 *) yellowLight__CTL)
/* Drive Modes */
#define yellowLight_DM0                    (* (reg8 *) yellowLight__DM0) 
#define yellowLight_DM1                    (* (reg8 *) yellowLight__DM1)
#define yellowLight_DM2                    (* (reg8 *) yellowLight__DM2) 
/* Input Buffer Disable Override */
#define yellowLight_INP_DIS                (* (reg8 *) yellowLight__INP_DIS)
/* LCD Common or Segment Drive */
#define yellowLight_LCD_COM_SEG            (* (reg8 *) yellowLight__LCD_COM_SEG)
/* Enable Segment LCD */
#define yellowLight_LCD_EN                 (* (reg8 *) yellowLight__LCD_EN)
/* Slew Rate Control */
#define yellowLight_SLW                    (* (reg8 *) yellowLight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define yellowLight_PRTDSI__CAPS_SEL       (* (reg8 *) yellowLight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define yellowLight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) yellowLight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define yellowLight_PRTDSI__OE_SEL0        (* (reg8 *) yellowLight__PRTDSI__OE_SEL0) 
#define yellowLight_PRTDSI__OE_SEL1        (* (reg8 *) yellowLight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define yellowLight_PRTDSI__OUT_SEL0       (* (reg8 *) yellowLight__PRTDSI__OUT_SEL0) 
#define yellowLight_PRTDSI__OUT_SEL1       (* (reg8 *) yellowLight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define yellowLight_PRTDSI__SYNC_OUT       (* (reg8 *) yellowLight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(yellowLight__SIO_CFG)
    #define yellowLight_SIO_HYST_EN        (* (reg8 *) yellowLight__SIO_HYST_EN)
    #define yellowLight_SIO_REG_HIFREQ     (* (reg8 *) yellowLight__SIO_REG_HIFREQ)
    #define yellowLight_SIO_CFG            (* (reg8 *) yellowLight__SIO_CFG)
    #define yellowLight_SIO_DIFF           (* (reg8 *) yellowLight__SIO_DIFF)
#endif /* (yellowLight__SIO_CFG) */

/* Interrupt Registers */
#if defined(yellowLight__INTSTAT)
    #define yellowLight_INTSTAT            (* (reg8 *) yellowLight__INTSTAT)
    #define yellowLight_SNAP               (* (reg8 *) yellowLight__SNAP)
    
	#define yellowLight_0_INTTYPE_REG 		(* (reg8 *) yellowLight__0__INTTYPE)
#endif /* (yellowLight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_yellowLight_H */


/* [] END OF FILE */
