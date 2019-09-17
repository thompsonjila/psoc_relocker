/*******************************************************************************
* File Name: orangeLight.h  
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

#if !defined(CY_PINS_orangeLight_H) /* Pins orangeLight_H */
#define CY_PINS_orangeLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "orangeLight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 orangeLight__PORT == 15 && ((orangeLight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    orangeLight_Write(uint8 value);
void    orangeLight_SetDriveMode(uint8 mode);
uint8   orangeLight_ReadDataReg(void);
uint8   orangeLight_Read(void);
void    orangeLight_SetInterruptMode(uint16 position, uint16 mode);
uint8   orangeLight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the orangeLight_SetDriveMode() function.
     *  @{
     */
        #define orangeLight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define orangeLight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define orangeLight_DM_RES_UP          PIN_DM_RES_UP
        #define orangeLight_DM_RES_DWN         PIN_DM_RES_DWN
        #define orangeLight_DM_OD_LO           PIN_DM_OD_LO
        #define orangeLight_DM_OD_HI           PIN_DM_OD_HI
        #define orangeLight_DM_STRONG          PIN_DM_STRONG
        #define orangeLight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define orangeLight_MASK               orangeLight__MASK
#define orangeLight_SHIFT              orangeLight__SHIFT
#define orangeLight_WIDTH              1u

/* Interrupt constants */
#if defined(orangeLight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in orangeLight_SetInterruptMode() function.
     *  @{
     */
        #define orangeLight_INTR_NONE      (uint16)(0x0000u)
        #define orangeLight_INTR_RISING    (uint16)(0x0001u)
        #define orangeLight_INTR_FALLING   (uint16)(0x0002u)
        #define orangeLight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define orangeLight_INTR_MASK      (0x01u) 
#endif /* (orangeLight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define orangeLight_PS                     (* (reg8 *) orangeLight__PS)
/* Data Register */
#define orangeLight_DR                     (* (reg8 *) orangeLight__DR)
/* Port Number */
#define orangeLight_PRT_NUM                (* (reg8 *) orangeLight__PRT) 
/* Connect to Analog Globals */                                                  
#define orangeLight_AG                     (* (reg8 *) orangeLight__AG)                       
/* Analog MUX bux enable */
#define orangeLight_AMUX                   (* (reg8 *) orangeLight__AMUX) 
/* Bidirectional Enable */                                                        
#define orangeLight_BIE                    (* (reg8 *) orangeLight__BIE)
/* Bit-mask for Aliased Register Access */
#define orangeLight_BIT_MASK               (* (reg8 *) orangeLight__BIT_MASK)
/* Bypass Enable */
#define orangeLight_BYP                    (* (reg8 *) orangeLight__BYP)
/* Port wide control signals */                                                   
#define orangeLight_CTL                    (* (reg8 *) orangeLight__CTL)
/* Drive Modes */
#define orangeLight_DM0                    (* (reg8 *) orangeLight__DM0) 
#define orangeLight_DM1                    (* (reg8 *) orangeLight__DM1)
#define orangeLight_DM2                    (* (reg8 *) orangeLight__DM2) 
/* Input Buffer Disable Override */
#define orangeLight_INP_DIS                (* (reg8 *) orangeLight__INP_DIS)
/* LCD Common or Segment Drive */
#define orangeLight_LCD_COM_SEG            (* (reg8 *) orangeLight__LCD_COM_SEG)
/* Enable Segment LCD */
#define orangeLight_LCD_EN                 (* (reg8 *) orangeLight__LCD_EN)
/* Slew Rate Control */
#define orangeLight_SLW                    (* (reg8 *) orangeLight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define orangeLight_PRTDSI__CAPS_SEL       (* (reg8 *) orangeLight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define orangeLight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) orangeLight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define orangeLight_PRTDSI__OE_SEL0        (* (reg8 *) orangeLight__PRTDSI__OE_SEL0) 
#define orangeLight_PRTDSI__OE_SEL1        (* (reg8 *) orangeLight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define orangeLight_PRTDSI__OUT_SEL0       (* (reg8 *) orangeLight__PRTDSI__OUT_SEL0) 
#define orangeLight_PRTDSI__OUT_SEL1       (* (reg8 *) orangeLight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define orangeLight_PRTDSI__SYNC_OUT       (* (reg8 *) orangeLight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(orangeLight__SIO_CFG)
    #define orangeLight_SIO_HYST_EN        (* (reg8 *) orangeLight__SIO_HYST_EN)
    #define orangeLight_SIO_REG_HIFREQ     (* (reg8 *) orangeLight__SIO_REG_HIFREQ)
    #define orangeLight_SIO_CFG            (* (reg8 *) orangeLight__SIO_CFG)
    #define orangeLight_SIO_DIFF           (* (reg8 *) orangeLight__SIO_DIFF)
#endif /* (orangeLight__SIO_CFG) */

/* Interrupt Registers */
#if defined(orangeLight__INTSTAT)
    #define orangeLight_INTSTAT            (* (reg8 *) orangeLight__INTSTAT)
    #define orangeLight_SNAP               (* (reg8 *) orangeLight__SNAP)
    
	#define orangeLight_0_INTTYPE_REG 		(* (reg8 *) orangeLight__0__INTTYPE)
#endif /* (orangeLight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_orangeLight_H */


/* [] END OF FILE */
