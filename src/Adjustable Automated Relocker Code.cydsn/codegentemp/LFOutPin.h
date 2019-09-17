/*******************************************************************************
* File Name: LFOutPin.h  
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

#if !defined(CY_PINS_LFOutPin_H) /* Pins LFOutPin_H */
#define CY_PINS_LFOutPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LFOutPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LFOutPin__PORT == 15 && ((LFOutPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LFOutPin_Write(uint8 value);
void    LFOutPin_SetDriveMode(uint8 mode);
uint8   LFOutPin_ReadDataReg(void);
uint8   LFOutPin_Read(void);
void    LFOutPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   LFOutPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LFOutPin_SetDriveMode() function.
     *  @{
     */
        #define LFOutPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LFOutPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LFOutPin_DM_RES_UP          PIN_DM_RES_UP
        #define LFOutPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define LFOutPin_DM_OD_LO           PIN_DM_OD_LO
        #define LFOutPin_DM_OD_HI           PIN_DM_OD_HI
        #define LFOutPin_DM_STRONG          PIN_DM_STRONG
        #define LFOutPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LFOutPin_MASK               LFOutPin__MASK
#define LFOutPin_SHIFT              LFOutPin__SHIFT
#define LFOutPin_WIDTH              1u

/* Interrupt constants */
#if defined(LFOutPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LFOutPin_SetInterruptMode() function.
     *  @{
     */
        #define LFOutPin_INTR_NONE      (uint16)(0x0000u)
        #define LFOutPin_INTR_RISING    (uint16)(0x0001u)
        #define LFOutPin_INTR_FALLING   (uint16)(0x0002u)
        #define LFOutPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LFOutPin_INTR_MASK      (0x01u) 
#endif /* (LFOutPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LFOutPin_PS                     (* (reg8 *) LFOutPin__PS)
/* Data Register */
#define LFOutPin_DR                     (* (reg8 *) LFOutPin__DR)
/* Port Number */
#define LFOutPin_PRT_NUM                (* (reg8 *) LFOutPin__PRT) 
/* Connect to Analog Globals */                                                  
#define LFOutPin_AG                     (* (reg8 *) LFOutPin__AG)                       
/* Analog MUX bux enable */
#define LFOutPin_AMUX                   (* (reg8 *) LFOutPin__AMUX) 
/* Bidirectional Enable */                                                        
#define LFOutPin_BIE                    (* (reg8 *) LFOutPin__BIE)
/* Bit-mask for Aliased Register Access */
#define LFOutPin_BIT_MASK               (* (reg8 *) LFOutPin__BIT_MASK)
/* Bypass Enable */
#define LFOutPin_BYP                    (* (reg8 *) LFOutPin__BYP)
/* Port wide control signals */                                                   
#define LFOutPin_CTL                    (* (reg8 *) LFOutPin__CTL)
/* Drive Modes */
#define LFOutPin_DM0                    (* (reg8 *) LFOutPin__DM0) 
#define LFOutPin_DM1                    (* (reg8 *) LFOutPin__DM1)
#define LFOutPin_DM2                    (* (reg8 *) LFOutPin__DM2) 
/* Input Buffer Disable Override */
#define LFOutPin_INP_DIS                (* (reg8 *) LFOutPin__INP_DIS)
/* LCD Common or Segment Drive */
#define LFOutPin_LCD_COM_SEG            (* (reg8 *) LFOutPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define LFOutPin_LCD_EN                 (* (reg8 *) LFOutPin__LCD_EN)
/* Slew Rate Control */
#define LFOutPin_SLW                    (* (reg8 *) LFOutPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LFOutPin_PRTDSI__CAPS_SEL       (* (reg8 *) LFOutPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LFOutPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LFOutPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LFOutPin_PRTDSI__OE_SEL0        (* (reg8 *) LFOutPin__PRTDSI__OE_SEL0) 
#define LFOutPin_PRTDSI__OE_SEL1        (* (reg8 *) LFOutPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LFOutPin_PRTDSI__OUT_SEL0       (* (reg8 *) LFOutPin__PRTDSI__OUT_SEL0) 
#define LFOutPin_PRTDSI__OUT_SEL1       (* (reg8 *) LFOutPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LFOutPin_PRTDSI__SYNC_OUT       (* (reg8 *) LFOutPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LFOutPin__SIO_CFG)
    #define LFOutPin_SIO_HYST_EN        (* (reg8 *) LFOutPin__SIO_HYST_EN)
    #define LFOutPin_SIO_REG_HIFREQ     (* (reg8 *) LFOutPin__SIO_REG_HIFREQ)
    #define LFOutPin_SIO_CFG            (* (reg8 *) LFOutPin__SIO_CFG)
    #define LFOutPin_SIO_DIFF           (* (reg8 *) LFOutPin__SIO_DIFF)
#endif /* (LFOutPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(LFOutPin__INTSTAT)
    #define LFOutPin_INTSTAT            (* (reg8 *) LFOutPin__INTSTAT)
    #define LFOutPin_SNAP               (* (reg8 *) LFOutPin__SNAP)
    
	#define LFOutPin_0_INTTYPE_REG 		(* (reg8 *) LFOutPin__0__INTTYPE)
#endif /* (LFOutPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LFOutPin_H */


/* [] END OF FILE */
