/*******************************************************************************
* File Name: calibratePin.h  
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

#if !defined(CY_PINS_calibratePin_H) /* Pins calibratePin_H */
#define CY_PINS_calibratePin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "calibratePin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 calibratePin__PORT == 15 && ((calibratePin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    calibratePin_Write(uint8 value);
void    calibratePin_SetDriveMode(uint8 mode);
uint8   calibratePin_ReadDataReg(void);
uint8   calibratePin_Read(void);
void    calibratePin_SetInterruptMode(uint16 position, uint16 mode);
uint8   calibratePin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the calibratePin_SetDriveMode() function.
     *  @{
     */
        #define calibratePin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define calibratePin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define calibratePin_DM_RES_UP          PIN_DM_RES_UP
        #define calibratePin_DM_RES_DWN         PIN_DM_RES_DWN
        #define calibratePin_DM_OD_LO           PIN_DM_OD_LO
        #define calibratePin_DM_OD_HI           PIN_DM_OD_HI
        #define calibratePin_DM_STRONG          PIN_DM_STRONG
        #define calibratePin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define calibratePin_MASK               calibratePin__MASK
#define calibratePin_SHIFT              calibratePin__SHIFT
#define calibratePin_WIDTH              1u

/* Interrupt constants */
#if defined(calibratePin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in calibratePin_SetInterruptMode() function.
     *  @{
     */
        #define calibratePin_INTR_NONE      (uint16)(0x0000u)
        #define calibratePin_INTR_RISING    (uint16)(0x0001u)
        #define calibratePin_INTR_FALLING   (uint16)(0x0002u)
        #define calibratePin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define calibratePin_INTR_MASK      (0x01u) 
#endif /* (calibratePin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define calibratePin_PS                     (* (reg8 *) calibratePin__PS)
/* Data Register */
#define calibratePin_DR                     (* (reg8 *) calibratePin__DR)
/* Port Number */
#define calibratePin_PRT_NUM                (* (reg8 *) calibratePin__PRT) 
/* Connect to Analog Globals */                                                  
#define calibratePin_AG                     (* (reg8 *) calibratePin__AG)                       
/* Analog MUX bux enable */
#define calibratePin_AMUX                   (* (reg8 *) calibratePin__AMUX) 
/* Bidirectional Enable */                                                        
#define calibratePin_BIE                    (* (reg8 *) calibratePin__BIE)
/* Bit-mask for Aliased Register Access */
#define calibratePin_BIT_MASK               (* (reg8 *) calibratePin__BIT_MASK)
/* Bypass Enable */
#define calibratePin_BYP                    (* (reg8 *) calibratePin__BYP)
/* Port wide control signals */                                                   
#define calibratePin_CTL                    (* (reg8 *) calibratePin__CTL)
/* Drive Modes */
#define calibratePin_DM0                    (* (reg8 *) calibratePin__DM0) 
#define calibratePin_DM1                    (* (reg8 *) calibratePin__DM1)
#define calibratePin_DM2                    (* (reg8 *) calibratePin__DM2) 
/* Input Buffer Disable Override */
#define calibratePin_INP_DIS                (* (reg8 *) calibratePin__INP_DIS)
/* LCD Common or Segment Drive */
#define calibratePin_LCD_COM_SEG            (* (reg8 *) calibratePin__LCD_COM_SEG)
/* Enable Segment LCD */
#define calibratePin_LCD_EN                 (* (reg8 *) calibratePin__LCD_EN)
/* Slew Rate Control */
#define calibratePin_SLW                    (* (reg8 *) calibratePin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define calibratePin_PRTDSI__CAPS_SEL       (* (reg8 *) calibratePin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define calibratePin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) calibratePin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define calibratePin_PRTDSI__OE_SEL0        (* (reg8 *) calibratePin__PRTDSI__OE_SEL0) 
#define calibratePin_PRTDSI__OE_SEL1        (* (reg8 *) calibratePin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define calibratePin_PRTDSI__OUT_SEL0       (* (reg8 *) calibratePin__PRTDSI__OUT_SEL0) 
#define calibratePin_PRTDSI__OUT_SEL1       (* (reg8 *) calibratePin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define calibratePin_PRTDSI__SYNC_OUT       (* (reg8 *) calibratePin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(calibratePin__SIO_CFG)
    #define calibratePin_SIO_HYST_EN        (* (reg8 *) calibratePin__SIO_HYST_EN)
    #define calibratePin_SIO_REG_HIFREQ     (* (reg8 *) calibratePin__SIO_REG_HIFREQ)
    #define calibratePin_SIO_CFG            (* (reg8 *) calibratePin__SIO_CFG)
    #define calibratePin_SIO_DIFF           (* (reg8 *) calibratePin__SIO_DIFF)
#endif /* (calibratePin__SIO_CFG) */

/* Interrupt Registers */
#if defined(calibratePin__INTSTAT)
    #define calibratePin_INTSTAT            (* (reg8 *) calibratePin__INTSTAT)
    #define calibratePin_SNAP               (* (reg8 *) calibratePin__SNAP)
    
	#define calibratePin_0_INTTYPE_REG 		(* (reg8 *) calibratePin__0__INTTYPE)
#endif /* (calibratePin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_calibratePin_H */


/* [] END OF FILE */
