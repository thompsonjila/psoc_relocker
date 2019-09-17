/*******************************************************************************
* File Name: setting8V.h  
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

#if !defined(CY_PINS_setting8V_H) /* Pins setting8V_H */
#define CY_PINS_setting8V_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "setting8V_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 setting8V__PORT == 15 && ((setting8V__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    setting8V_Write(uint8 value);
void    setting8V_SetDriveMode(uint8 mode);
uint8   setting8V_ReadDataReg(void);
uint8   setting8V_Read(void);
void    setting8V_SetInterruptMode(uint16 position, uint16 mode);
uint8   setting8V_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the setting8V_SetDriveMode() function.
     *  @{
     */
        #define setting8V_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define setting8V_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define setting8V_DM_RES_UP          PIN_DM_RES_UP
        #define setting8V_DM_RES_DWN         PIN_DM_RES_DWN
        #define setting8V_DM_OD_LO           PIN_DM_OD_LO
        #define setting8V_DM_OD_HI           PIN_DM_OD_HI
        #define setting8V_DM_STRONG          PIN_DM_STRONG
        #define setting8V_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define setting8V_MASK               setting8V__MASK
#define setting8V_SHIFT              setting8V__SHIFT
#define setting8V_WIDTH              1u

/* Interrupt constants */
#if defined(setting8V__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in setting8V_SetInterruptMode() function.
     *  @{
     */
        #define setting8V_INTR_NONE      (uint16)(0x0000u)
        #define setting8V_INTR_RISING    (uint16)(0x0001u)
        #define setting8V_INTR_FALLING   (uint16)(0x0002u)
        #define setting8V_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define setting8V_INTR_MASK      (0x01u) 
#endif /* (setting8V__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define setting8V_PS                     (* (reg8 *) setting8V__PS)
/* Data Register */
#define setting8V_DR                     (* (reg8 *) setting8V__DR)
/* Port Number */
#define setting8V_PRT_NUM                (* (reg8 *) setting8V__PRT) 
/* Connect to Analog Globals */                                                  
#define setting8V_AG                     (* (reg8 *) setting8V__AG)                       
/* Analog MUX bux enable */
#define setting8V_AMUX                   (* (reg8 *) setting8V__AMUX) 
/* Bidirectional Enable */                                                        
#define setting8V_BIE                    (* (reg8 *) setting8V__BIE)
/* Bit-mask for Aliased Register Access */
#define setting8V_BIT_MASK               (* (reg8 *) setting8V__BIT_MASK)
/* Bypass Enable */
#define setting8V_BYP                    (* (reg8 *) setting8V__BYP)
/* Port wide control signals */                                                   
#define setting8V_CTL                    (* (reg8 *) setting8V__CTL)
/* Drive Modes */
#define setting8V_DM0                    (* (reg8 *) setting8V__DM0) 
#define setting8V_DM1                    (* (reg8 *) setting8V__DM1)
#define setting8V_DM2                    (* (reg8 *) setting8V__DM2) 
/* Input Buffer Disable Override */
#define setting8V_INP_DIS                (* (reg8 *) setting8V__INP_DIS)
/* LCD Common or Segment Drive */
#define setting8V_LCD_COM_SEG            (* (reg8 *) setting8V__LCD_COM_SEG)
/* Enable Segment LCD */
#define setting8V_LCD_EN                 (* (reg8 *) setting8V__LCD_EN)
/* Slew Rate Control */
#define setting8V_SLW                    (* (reg8 *) setting8V__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define setting8V_PRTDSI__CAPS_SEL       (* (reg8 *) setting8V__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define setting8V_PRTDSI__DBL_SYNC_IN    (* (reg8 *) setting8V__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define setting8V_PRTDSI__OE_SEL0        (* (reg8 *) setting8V__PRTDSI__OE_SEL0) 
#define setting8V_PRTDSI__OE_SEL1        (* (reg8 *) setting8V__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define setting8V_PRTDSI__OUT_SEL0       (* (reg8 *) setting8V__PRTDSI__OUT_SEL0) 
#define setting8V_PRTDSI__OUT_SEL1       (* (reg8 *) setting8V__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define setting8V_PRTDSI__SYNC_OUT       (* (reg8 *) setting8V__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(setting8V__SIO_CFG)
    #define setting8V_SIO_HYST_EN        (* (reg8 *) setting8V__SIO_HYST_EN)
    #define setting8V_SIO_REG_HIFREQ     (* (reg8 *) setting8V__SIO_REG_HIFREQ)
    #define setting8V_SIO_CFG            (* (reg8 *) setting8V__SIO_CFG)
    #define setting8V_SIO_DIFF           (* (reg8 *) setting8V__SIO_DIFF)
#endif /* (setting8V__SIO_CFG) */

/* Interrupt Registers */
#if defined(setting8V__INTSTAT)
    #define setting8V_INTSTAT            (* (reg8 *) setting8V__INTSTAT)
    #define setting8V_SNAP               (* (reg8 *) setting8V__SNAP)
    
	#define setting8V_0_INTTYPE_REG 		(* (reg8 *) setting8V__0__INTTYPE)
#endif /* (setting8V__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_setting8V_H */


/* [] END OF FILE */
