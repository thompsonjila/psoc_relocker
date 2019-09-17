/*******************************************************************************
* File Name: lockIn.h  
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

#if !defined(CY_PINS_lockIn_H) /* Pins lockIn_H */
#define CY_PINS_lockIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "lockIn_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 lockIn__PORT == 15 && ((lockIn__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    lockIn_Write(uint8 value);
void    lockIn_SetDriveMode(uint8 mode);
uint8   lockIn_ReadDataReg(void);
uint8   lockIn_Read(void);
void    lockIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   lockIn_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the lockIn_SetDriveMode() function.
     *  @{
     */
        #define lockIn_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define lockIn_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define lockIn_DM_RES_UP          PIN_DM_RES_UP
        #define lockIn_DM_RES_DWN         PIN_DM_RES_DWN
        #define lockIn_DM_OD_LO           PIN_DM_OD_LO
        #define lockIn_DM_OD_HI           PIN_DM_OD_HI
        #define lockIn_DM_STRONG          PIN_DM_STRONG
        #define lockIn_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define lockIn_MASK               lockIn__MASK
#define lockIn_SHIFT              lockIn__SHIFT
#define lockIn_WIDTH              1u

/* Interrupt constants */
#if defined(lockIn__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in lockIn_SetInterruptMode() function.
     *  @{
     */
        #define lockIn_INTR_NONE      (uint16)(0x0000u)
        #define lockIn_INTR_RISING    (uint16)(0x0001u)
        #define lockIn_INTR_FALLING   (uint16)(0x0002u)
        #define lockIn_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define lockIn_INTR_MASK      (0x01u) 
#endif /* (lockIn__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define lockIn_PS                     (* (reg8 *) lockIn__PS)
/* Data Register */
#define lockIn_DR                     (* (reg8 *) lockIn__DR)
/* Port Number */
#define lockIn_PRT_NUM                (* (reg8 *) lockIn__PRT) 
/* Connect to Analog Globals */                                                  
#define lockIn_AG                     (* (reg8 *) lockIn__AG)                       
/* Analog MUX bux enable */
#define lockIn_AMUX                   (* (reg8 *) lockIn__AMUX) 
/* Bidirectional Enable */                                                        
#define lockIn_BIE                    (* (reg8 *) lockIn__BIE)
/* Bit-mask for Aliased Register Access */
#define lockIn_BIT_MASK               (* (reg8 *) lockIn__BIT_MASK)
/* Bypass Enable */
#define lockIn_BYP                    (* (reg8 *) lockIn__BYP)
/* Port wide control signals */                                                   
#define lockIn_CTL                    (* (reg8 *) lockIn__CTL)
/* Drive Modes */
#define lockIn_DM0                    (* (reg8 *) lockIn__DM0) 
#define lockIn_DM1                    (* (reg8 *) lockIn__DM1)
#define lockIn_DM2                    (* (reg8 *) lockIn__DM2) 
/* Input Buffer Disable Override */
#define lockIn_INP_DIS                (* (reg8 *) lockIn__INP_DIS)
/* LCD Common or Segment Drive */
#define lockIn_LCD_COM_SEG            (* (reg8 *) lockIn__LCD_COM_SEG)
/* Enable Segment LCD */
#define lockIn_LCD_EN                 (* (reg8 *) lockIn__LCD_EN)
/* Slew Rate Control */
#define lockIn_SLW                    (* (reg8 *) lockIn__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define lockIn_PRTDSI__CAPS_SEL       (* (reg8 *) lockIn__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define lockIn_PRTDSI__DBL_SYNC_IN    (* (reg8 *) lockIn__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define lockIn_PRTDSI__OE_SEL0        (* (reg8 *) lockIn__PRTDSI__OE_SEL0) 
#define lockIn_PRTDSI__OE_SEL1        (* (reg8 *) lockIn__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define lockIn_PRTDSI__OUT_SEL0       (* (reg8 *) lockIn__PRTDSI__OUT_SEL0) 
#define lockIn_PRTDSI__OUT_SEL1       (* (reg8 *) lockIn__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define lockIn_PRTDSI__SYNC_OUT       (* (reg8 *) lockIn__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(lockIn__SIO_CFG)
    #define lockIn_SIO_HYST_EN        (* (reg8 *) lockIn__SIO_HYST_EN)
    #define lockIn_SIO_REG_HIFREQ     (* (reg8 *) lockIn__SIO_REG_HIFREQ)
    #define lockIn_SIO_CFG            (* (reg8 *) lockIn__SIO_CFG)
    #define lockIn_SIO_DIFF           (* (reg8 *) lockIn__SIO_DIFF)
#endif /* (lockIn__SIO_CFG) */

/* Interrupt Registers */
#if defined(lockIn__INTSTAT)
    #define lockIn_INTSTAT            (* (reg8 *) lockIn__INTSTAT)
    #define lockIn_SNAP               (* (reg8 *) lockIn__SNAP)
    
	#define lockIn_0_INTTYPE_REG 		(* (reg8 *) lockIn__0__INTTYPE)
#endif /* (lockIn__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_lockIn_H */


/* [] END OF FILE */
