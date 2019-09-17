/*******************************************************************************
* File Name: setting28V.h  
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

#if !defined(CY_PINS_setting28V_H) /* Pins setting28V_H */
#define CY_PINS_setting28V_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "setting28V_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 setting28V__PORT == 15 && ((setting28V__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    setting28V_Write(uint8 value);
void    setting28V_SetDriveMode(uint8 mode);
uint8   setting28V_ReadDataReg(void);
uint8   setting28V_Read(void);
void    setting28V_SetInterruptMode(uint16 position, uint16 mode);
uint8   setting28V_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the setting28V_SetDriveMode() function.
     *  @{
     */
        #define setting28V_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define setting28V_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define setting28V_DM_RES_UP          PIN_DM_RES_UP
        #define setting28V_DM_RES_DWN         PIN_DM_RES_DWN
        #define setting28V_DM_OD_LO           PIN_DM_OD_LO
        #define setting28V_DM_OD_HI           PIN_DM_OD_HI
        #define setting28V_DM_STRONG          PIN_DM_STRONG
        #define setting28V_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define setting28V_MASK               setting28V__MASK
#define setting28V_SHIFT              setting28V__SHIFT
#define setting28V_WIDTH              1u

/* Interrupt constants */
#if defined(setting28V__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in setting28V_SetInterruptMode() function.
     *  @{
     */
        #define setting28V_INTR_NONE      (uint16)(0x0000u)
        #define setting28V_INTR_RISING    (uint16)(0x0001u)
        #define setting28V_INTR_FALLING   (uint16)(0x0002u)
        #define setting28V_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define setting28V_INTR_MASK      (0x01u) 
#endif /* (setting28V__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define setting28V_PS                     (* (reg8 *) setting28V__PS)
/* Data Register */
#define setting28V_DR                     (* (reg8 *) setting28V__DR)
/* Port Number */
#define setting28V_PRT_NUM                (* (reg8 *) setting28V__PRT) 
/* Connect to Analog Globals */                                                  
#define setting28V_AG                     (* (reg8 *) setting28V__AG)                       
/* Analog MUX bux enable */
#define setting28V_AMUX                   (* (reg8 *) setting28V__AMUX) 
/* Bidirectional Enable */                                                        
#define setting28V_BIE                    (* (reg8 *) setting28V__BIE)
/* Bit-mask for Aliased Register Access */
#define setting28V_BIT_MASK               (* (reg8 *) setting28V__BIT_MASK)
/* Bypass Enable */
#define setting28V_BYP                    (* (reg8 *) setting28V__BYP)
/* Port wide control signals */                                                   
#define setting28V_CTL                    (* (reg8 *) setting28V__CTL)
/* Drive Modes */
#define setting28V_DM0                    (* (reg8 *) setting28V__DM0) 
#define setting28V_DM1                    (* (reg8 *) setting28V__DM1)
#define setting28V_DM2                    (* (reg8 *) setting28V__DM2) 
/* Input Buffer Disable Override */
#define setting28V_INP_DIS                (* (reg8 *) setting28V__INP_DIS)
/* LCD Common or Segment Drive */
#define setting28V_LCD_COM_SEG            (* (reg8 *) setting28V__LCD_COM_SEG)
/* Enable Segment LCD */
#define setting28V_LCD_EN                 (* (reg8 *) setting28V__LCD_EN)
/* Slew Rate Control */
#define setting28V_SLW                    (* (reg8 *) setting28V__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define setting28V_PRTDSI__CAPS_SEL       (* (reg8 *) setting28V__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define setting28V_PRTDSI__DBL_SYNC_IN    (* (reg8 *) setting28V__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define setting28V_PRTDSI__OE_SEL0        (* (reg8 *) setting28V__PRTDSI__OE_SEL0) 
#define setting28V_PRTDSI__OE_SEL1        (* (reg8 *) setting28V__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define setting28V_PRTDSI__OUT_SEL0       (* (reg8 *) setting28V__PRTDSI__OUT_SEL0) 
#define setting28V_PRTDSI__OUT_SEL1       (* (reg8 *) setting28V__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define setting28V_PRTDSI__SYNC_OUT       (* (reg8 *) setting28V__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(setting28V__SIO_CFG)
    #define setting28V_SIO_HYST_EN        (* (reg8 *) setting28V__SIO_HYST_EN)
    #define setting28V_SIO_REG_HIFREQ     (* (reg8 *) setting28V__SIO_REG_HIFREQ)
    #define setting28V_SIO_CFG            (* (reg8 *) setting28V__SIO_CFG)
    #define setting28V_SIO_DIFF           (* (reg8 *) setting28V__SIO_DIFF)
#endif /* (setting28V__SIO_CFG) */

/* Interrupt Registers */
#if defined(setting28V__INTSTAT)
    #define setting28V_INTSTAT            (* (reg8 *) setting28V__INTSTAT)
    #define setting28V_SNAP               (* (reg8 *) setting28V__SNAP)
    
	#define setting28V_0_INTTYPE_REG 		(* (reg8 *) setting28V__0__INTTYPE)
#endif /* (setting28V__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_setting28V_H */


/* [] END OF FILE */
