/*******************************************************************************
* File Name: tempTrigger.h  
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

#if !defined(CY_PINS_tempTrigger_H) /* Pins tempTrigger_H */
#define CY_PINS_tempTrigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "tempTrigger_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 tempTrigger__PORT == 15 && ((tempTrigger__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    tempTrigger_Write(uint8 value);
void    tempTrigger_SetDriveMode(uint8 mode);
uint8   tempTrigger_ReadDataReg(void);
uint8   tempTrigger_Read(void);
void    tempTrigger_SetInterruptMode(uint16 position, uint16 mode);
uint8   tempTrigger_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the tempTrigger_SetDriveMode() function.
     *  @{
     */
        #define tempTrigger_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define tempTrigger_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define tempTrigger_DM_RES_UP          PIN_DM_RES_UP
        #define tempTrigger_DM_RES_DWN         PIN_DM_RES_DWN
        #define tempTrigger_DM_OD_LO           PIN_DM_OD_LO
        #define tempTrigger_DM_OD_HI           PIN_DM_OD_HI
        #define tempTrigger_DM_STRONG          PIN_DM_STRONG
        #define tempTrigger_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define tempTrigger_MASK               tempTrigger__MASK
#define tempTrigger_SHIFT              tempTrigger__SHIFT
#define tempTrigger_WIDTH              1u

/* Interrupt constants */
#if defined(tempTrigger__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in tempTrigger_SetInterruptMode() function.
     *  @{
     */
        #define tempTrigger_INTR_NONE      (uint16)(0x0000u)
        #define tempTrigger_INTR_RISING    (uint16)(0x0001u)
        #define tempTrigger_INTR_FALLING   (uint16)(0x0002u)
        #define tempTrigger_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define tempTrigger_INTR_MASK      (0x01u) 
#endif /* (tempTrigger__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define tempTrigger_PS                     (* (reg8 *) tempTrigger__PS)
/* Data Register */
#define tempTrigger_DR                     (* (reg8 *) tempTrigger__DR)
/* Port Number */
#define tempTrigger_PRT_NUM                (* (reg8 *) tempTrigger__PRT) 
/* Connect to Analog Globals */                                                  
#define tempTrigger_AG                     (* (reg8 *) tempTrigger__AG)                       
/* Analog MUX bux enable */
#define tempTrigger_AMUX                   (* (reg8 *) tempTrigger__AMUX) 
/* Bidirectional Enable */                                                        
#define tempTrigger_BIE                    (* (reg8 *) tempTrigger__BIE)
/* Bit-mask for Aliased Register Access */
#define tempTrigger_BIT_MASK               (* (reg8 *) tempTrigger__BIT_MASK)
/* Bypass Enable */
#define tempTrigger_BYP                    (* (reg8 *) tempTrigger__BYP)
/* Port wide control signals */                                                   
#define tempTrigger_CTL                    (* (reg8 *) tempTrigger__CTL)
/* Drive Modes */
#define tempTrigger_DM0                    (* (reg8 *) tempTrigger__DM0) 
#define tempTrigger_DM1                    (* (reg8 *) tempTrigger__DM1)
#define tempTrigger_DM2                    (* (reg8 *) tempTrigger__DM2) 
/* Input Buffer Disable Override */
#define tempTrigger_INP_DIS                (* (reg8 *) tempTrigger__INP_DIS)
/* LCD Common or Segment Drive */
#define tempTrigger_LCD_COM_SEG            (* (reg8 *) tempTrigger__LCD_COM_SEG)
/* Enable Segment LCD */
#define tempTrigger_LCD_EN                 (* (reg8 *) tempTrigger__LCD_EN)
/* Slew Rate Control */
#define tempTrigger_SLW                    (* (reg8 *) tempTrigger__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define tempTrigger_PRTDSI__CAPS_SEL       (* (reg8 *) tempTrigger__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define tempTrigger_PRTDSI__DBL_SYNC_IN    (* (reg8 *) tempTrigger__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define tempTrigger_PRTDSI__OE_SEL0        (* (reg8 *) tempTrigger__PRTDSI__OE_SEL0) 
#define tempTrigger_PRTDSI__OE_SEL1        (* (reg8 *) tempTrigger__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define tempTrigger_PRTDSI__OUT_SEL0       (* (reg8 *) tempTrigger__PRTDSI__OUT_SEL0) 
#define tempTrigger_PRTDSI__OUT_SEL1       (* (reg8 *) tempTrigger__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define tempTrigger_PRTDSI__SYNC_OUT       (* (reg8 *) tempTrigger__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(tempTrigger__SIO_CFG)
    #define tempTrigger_SIO_HYST_EN        (* (reg8 *) tempTrigger__SIO_HYST_EN)
    #define tempTrigger_SIO_REG_HIFREQ     (* (reg8 *) tempTrigger__SIO_REG_HIFREQ)
    #define tempTrigger_SIO_CFG            (* (reg8 *) tempTrigger__SIO_CFG)
    #define tempTrigger_SIO_DIFF           (* (reg8 *) tempTrigger__SIO_DIFF)
#endif /* (tempTrigger__SIO_CFG) */

/* Interrupt Registers */
#if defined(tempTrigger__INTSTAT)
    #define tempTrigger_INTSTAT            (* (reg8 *) tempTrigger__INTSTAT)
    #define tempTrigger_SNAP               (* (reg8 *) tempTrigger__SNAP)
    
	#define tempTrigger_0_INTTYPE_REG 		(* (reg8 *) tempTrigger__0__INTTYPE)
#endif /* (tempTrigger__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_tempTrigger_H */


/* [] END OF FILE */
