/*******************************************************************************
* File Name: blockLockPin.h  
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

#if !defined(CY_PINS_blockLockPin_H) /* Pins blockLockPin_H */
#define CY_PINS_blockLockPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "blockLockPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 blockLockPin__PORT == 15 && ((blockLockPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    blockLockPin_Write(uint8 value);
void    blockLockPin_SetDriveMode(uint8 mode);
uint8   blockLockPin_ReadDataReg(void);
uint8   blockLockPin_Read(void);
void    blockLockPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   blockLockPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the blockLockPin_SetDriveMode() function.
     *  @{
     */
        #define blockLockPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define blockLockPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define blockLockPin_DM_RES_UP          PIN_DM_RES_UP
        #define blockLockPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define blockLockPin_DM_OD_LO           PIN_DM_OD_LO
        #define blockLockPin_DM_OD_HI           PIN_DM_OD_HI
        #define blockLockPin_DM_STRONG          PIN_DM_STRONG
        #define blockLockPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define blockLockPin_MASK               blockLockPin__MASK
#define blockLockPin_SHIFT              blockLockPin__SHIFT
#define blockLockPin_WIDTH              1u

/* Interrupt constants */
#if defined(blockLockPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in blockLockPin_SetInterruptMode() function.
     *  @{
     */
        #define blockLockPin_INTR_NONE      (uint16)(0x0000u)
        #define blockLockPin_INTR_RISING    (uint16)(0x0001u)
        #define blockLockPin_INTR_FALLING   (uint16)(0x0002u)
        #define blockLockPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define blockLockPin_INTR_MASK      (0x01u) 
#endif /* (blockLockPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define blockLockPin_PS                     (* (reg8 *) blockLockPin__PS)
/* Data Register */
#define blockLockPin_DR                     (* (reg8 *) blockLockPin__DR)
/* Port Number */
#define blockLockPin_PRT_NUM                (* (reg8 *) blockLockPin__PRT) 
/* Connect to Analog Globals */                                                  
#define blockLockPin_AG                     (* (reg8 *) blockLockPin__AG)                       
/* Analog MUX bux enable */
#define blockLockPin_AMUX                   (* (reg8 *) blockLockPin__AMUX) 
/* Bidirectional Enable */                                                        
#define blockLockPin_BIE                    (* (reg8 *) blockLockPin__BIE)
/* Bit-mask for Aliased Register Access */
#define blockLockPin_BIT_MASK               (* (reg8 *) blockLockPin__BIT_MASK)
/* Bypass Enable */
#define blockLockPin_BYP                    (* (reg8 *) blockLockPin__BYP)
/* Port wide control signals */                                                   
#define blockLockPin_CTL                    (* (reg8 *) blockLockPin__CTL)
/* Drive Modes */
#define blockLockPin_DM0                    (* (reg8 *) blockLockPin__DM0) 
#define blockLockPin_DM1                    (* (reg8 *) blockLockPin__DM1)
#define blockLockPin_DM2                    (* (reg8 *) blockLockPin__DM2) 
/* Input Buffer Disable Override */
#define blockLockPin_INP_DIS                (* (reg8 *) blockLockPin__INP_DIS)
/* LCD Common or Segment Drive */
#define blockLockPin_LCD_COM_SEG            (* (reg8 *) blockLockPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define blockLockPin_LCD_EN                 (* (reg8 *) blockLockPin__LCD_EN)
/* Slew Rate Control */
#define blockLockPin_SLW                    (* (reg8 *) blockLockPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define blockLockPin_PRTDSI__CAPS_SEL       (* (reg8 *) blockLockPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define blockLockPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) blockLockPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define blockLockPin_PRTDSI__OE_SEL0        (* (reg8 *) blockLockPin__PRTDSI__OE_SEL0) 
#define blockLockPin_PRTDSI__OE_SEL1        (* (reg8 *) blockLockPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define blockLockPin_PRTDSI__OUT_SEL0       (* (reg8 *) blockLockPin__PRTDSI__OUT_SEL0) 
#define blockLockPin_PRTDSI__OUT_SEL1       (* (reg8 *) blockLockPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define blockLockPin_PRTDSI__SYNC_OUT       (* (reg8 *) blockLockPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(blockLockPin__SIO_CFG)
    #define blockLockPin_SIO_HYST_EN        (* (reg8 *) blockLockPin__SIO_HYST_EN)
    #define blockLockPin_SIO_REG_HIFREQ     (* (reg8 *) blockLockPin__SIO_REG_HIFREQ)
    #define blockLockPin_SIO_CFG            (* (reg8 *) blockLockPin__SIO_CFG)
    #define blockLockPin_SIO_DIFF           (* (reg8 *) blockLockPin__SIO_DIFF)
#endif /* (blockLockPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(blockLockPin__INTSTAT)
    #define blockLockPin_INTSTAT            (* (reg8 *) blockLockPin__INTSTAT)
    #define blockLockPin_SNAP               (* (reg8 *) blockLockPin__SNAP)
    
	#define blockLockPin_0_INTTYPE_REG 		(* (reg8 *) blockLockPin__0__INTTYPE)
#endif /* (blockLockPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_blockLockPin_H */


/* [] END OF FILE */
