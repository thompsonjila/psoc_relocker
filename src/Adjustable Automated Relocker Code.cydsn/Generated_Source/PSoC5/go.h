/*******************************************************************************
* File Name: go.h  
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

#if !defined(CY_PINS_go_H) /* Pins go_H */
#define CY_PINS_go_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "go_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 go__PORT == 15 && ((go__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    go_Write(uint8 value);
void    go_SetDriveMode(uint8 mode);
uint8   go_ReadDataReg(void);
uint8   go_Read(void);
void    go_SetInterruptMode(uint16 position, uint16 mode);
uint8   go_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the go_SetDriveMode() function.
     *  @{
     */
        #define go_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define go_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define go_DM_RES_UP          PIN_DM_RES_UP
        #define go_DM_RES_DWN         PIN_DM_RES_DWN
        #define go_DM_OD_LO           PIN_DM_OD_LO
        #define go_DM_OD_HI           PIN_DM_OD_HI
        #define go_DM_STRONG          PIN_DM_STRONG
        #define go_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define go_MASK               go__MASK
#define go_SHIFT              go__SHIFT
#define go_WIDTH              1u

/* Interrupt constants */
#if defined(go__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in go_SetInterruptMode() function.
     *  @{
     */
        #define go_INTR_NONE      (uint16)(0x0000u)
        #define go_INTR_RISING    (uint16)(0x0001u)
        #define go_INTR_FALLING   (uint16)(0x0002u)
        #define go_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define go_INTR_MASK      (0x01u) 
#endif /* (go__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define go_PS                     (* (reg8 *) go__PS)
/* Data Register */
#define go_DR                     (* (reg8 *) go__DR)
/* Port Number */
#define go_PRT_NUM                (* (reg8 *) go__PRT) 
/* Connect to Analog Globals */                                                  
#define go_AG                     (* (reg8 *) go__AG)                       
/* Analog MUX bux enable */
#define go_AMUX                   (* (reg8 *) go__AMUX) 
/* Bidirectional Enable */                                                        
#define go_BIE                    (* (reg8 *) go__BIE)
/* Bit-mask for Aliased Register Access */
#define go_BIT_MASK               (* (reg8 *) go__BIT_MASK)
/* Bypass Enable */
#define go_BYP                    (* (reg8 *) go__BYP)
/* Port wide control signals */                                                   
#define go_CTL                    (* (reg8 *) go__CTL)
/* Drive Modes */
#define go_DM0                    (* (reg8 *) go__DM0) 
#define go_DM1                    (* (reg8 *) go__DM1)
#define go_DM2                    (* (reg8 *) go__DM2) 
/* Input Buffer Disable Override */
#define go_INP_DIS                (* (reg8 *) go__INP_DIS)
/* LCD Common or Segment Drive */
#define go_LCD_COM_SEG            (* (reg8 *) go__LCD_COM_SEG)
/* Enable Segment LCD */
#define go_LCD_EN                 (* (reg8 *) go__LCD_EN)
/* Slew Rate Control */
#define go_SLW                    (* (reg8 *) go__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define go_PRTDSI__CAPS_SEL       (* (reg8 *) go__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define go_PRTDSI__DBL_SYNC_IN    (* (reg8 *) go__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define go_PRTDSI__OE_SEL0        (* (reg8 *) go__PRTDSI__OE_SEL0) 
#define go_PRTDSI__OE_SEL1        (* (reg8 *) go__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define go_PRTDSI__OUT_SEL0       (* (reg8 *) go__PRTDSI__OUT_SEL0) 
#define go_PRTDSI__OUT_SEL1       (* (reg8 *) go__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define go_PRTDSI__SYNC_OUT       (* (reg8 *) go__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(go__SIO_CFG)
    #define go_SIO_HYST_EN        (* (reg8 *) go__SIO_HYST_EN)
    #define go_SIO_REG_HIFREQ     (* (reg8 *) go__SIO_REG_HIFREQ)
    #define go_SIO_CFG            (* (reg8 *) go__SIO_CFG)
    #define go_SIO_DIFF           (* (reg8 *) go__SIO_DIFF)
#endif /* (go__SIO_CFG) */

/* Interrupt Registers */
#if defined(go__INTSTAT)
    #define go_INTSTAT            (* (reg8 *) go__INTSTAT)
    #define go_SNAP               (* (reg8 *) go__SNAP)
    
	#define go_0_INTTYPE_REG 		(* (reg8 *) go__0__INTTYPE)
#endif /* (go__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_go_H */


/* [] END OF FILE */
