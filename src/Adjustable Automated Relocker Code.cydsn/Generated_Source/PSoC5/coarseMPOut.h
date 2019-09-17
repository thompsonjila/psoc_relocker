/*******************************************************************************
* File Name: coarseMPOut.h  
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

#if !defined(CY_PINS_coarseMPOut_H) /* Pins coarseMPOut_H */
#define CY_PINS_coarseMPOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "coarseMPOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 coarseMPOut__PORT == 15 && ((coarseMPOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    coarseMPOut_Write(uint8 value);
void    coarseMPOut_SetDriveMode(uint8 mode);
uint8   coarseMPOut_ReadDataReg(void);
uint8   coarseMPOut_Read(void);
void    coarseMPOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   coarseMPOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the coarseMPOut_SetDriveMode() function.
     *  @{
     */
        #define coarseMPOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define coarseMPOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define coarseMPOut_DM_RES_UP          PIN_DM_RES_UP
        #define coarseMPOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define coarseMPOut_DM_OD_LO           PIN_DM_OD_LO
        #define coarseMPOut_DM_OD_HI           PIN_DM_OD_HI
        #define coarseMPOut_DM_STRONG          PIN_DM_STRONG
        #define coarseMPOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define coarseMPOut_MASK               coarseMPOut__MASK
#define coarseMPOut_SHIFT              coarseMPOut__SHIFT
#define coarseMPOut_WIDTH              1u

/* Interrupt constants */
#if defined(coarseMPOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in coarseMPOut_SetInterruptMode() function.
     *  @{
     */
        #define coarseMPOut_INTR_NONE      (uint16)(0x0000u)
        #define coarseMPOut_INTR_RISING    (uint16)(0x0001u)
        #define coarseMPOut_INTR_FALLING   (uint16)(0x0002u)
        #define coarseMPOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define coarseMPOut_INTR_MASK      (0x01u) 
#endif /* (coarseMPOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define coarseMPOut_PS                     (* (reg8 *) coarseMPOut__PS)
/* Data Register */
#define coarseMPOut_DR                     (* (reg8 *) coarseMPOut__DR)
/* Port Number */
#define coarseMPOut_PRT_NUM                (* (reg8 *) coarseMPOut__PRT) 
/* Connect to Analog Globals */                                                  
#define coarseMPOut_AG                     (* (reg8 *) coarseMPOut__AG)                       
/* Analog MUX bux enable */
#define coarseMPOut_AMUX                   (* (reg8 *) coarseMPOut__AMUX) 
/* Bidirectional Enable */                                                        
#define coarseMPOut_BIE                    (* (reg8 *) coarseMPOut__BIE)
/* Bit-mask for Aliased Register Access */
#define coarseMPOut_BIT_MASK               (* (reg8 *) coarseMPOut__BIT_MASK)
/* Bypass Enable */
#define coarseMPOut_BYP                    (* (reg8 *) coarseMPOut__BYP)
/* Port wide control signals */                                                   
#define coarseMPOut_CTL                    (* (reg8 *) coarseMPOut__CTL)
/* Drive Modes */
#define coarseMPOut_DM0                    (* (reg8 *) coarseMPOut__DM0) 
#define coarseMPOut_DM1                    (* (reg8 *) coarseMPOut__DM1)
#define coarseMPOut_DM2                    (* (reg8 *) coarseMPOut__DM2) 
/* Input Buffer Disable Override */
#define coarseMPOut_INP_DIS                (* (reg8 *) coarseMPOut__INP_DIS)
/* LCD Common or Segment Drive */
#define coarseMPOut_LCD_COM_SEG            (* (reg8 *) coarseMPOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define coarseMPOut_LCD_EN                 (* (reg8 *) coarseMPOut__LCD_EN)
/* Slew Rate Control */
#define coarseMPOut_SLW                    (* (reg8 *) coarseMPOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define coarseMPOut_PRTDSI__CAPS_SEL       (* (reg8 *) coarseMPOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define coarseMPOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) coarseMPOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define coarseMPOut_PRTDSI__OE_SEL0        (* (reg8 *) coarseMPOut__PRTDSI__OE_SEL0) 
#define coarseMPOut_PRTDSI__OE_SEL1        (* (reg8 *) coarseMPOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define coarseMPOut_PRTDSI__OUT_SEL0       (* (reg8 *) coarseMPOut__PRTDSI__OUT_SEL0) 
#define coarseMPOut_PRTDSI__OUT_SEL1       (* (reg8 *) coarseMPOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define coarseMPOut_PRTDSI__SYNC_OUT       (* (reg8 *) coarseMPOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(coarseMPOut__SIO_CFG)
    #define coarseMPOut_SIO_HYST_EN        (* (reg8 *) coarseMPOut__SIO_HYST_EN)
    #define coarseMPOut_SIO_REG_HIFREQ     (* (reg8 *) coarseMPOut__SIO_REG_HIFREQ)
    #define coarseMPOut_SIO_CFG            (* (reg8 *) coarseMPOut__SIO_CFG)
    #define coarseMPOut_SIO_DIFF           (* (reg8 *) coarseMPOut__SIO_DIFF)
#endif /* (coarseMPOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(coarseMPOut__INTSTAT)
    #define coarseMPOut_INTSTAT            (* (reg8 *) coarseMPOut__INTSTAT)
    #define coarseMPOut_SNAP               (* (reg8 *) coarseMPOut__SNAP)
    
	#define coarseMPOut_0_INTTYPE_REG 		(* (reg8 *) coarseMPOut__0__INTTYPE)
#endif /* (coarseMPOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_coarseMPOut_H */


/* [] END OF FILE */
