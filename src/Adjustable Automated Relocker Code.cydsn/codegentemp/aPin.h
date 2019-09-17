/*******************************************************************************
* File Name: aPin.h  
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

#if !defined(CY_PINS_aPin_H) /* Pins aPin_H */
#define CY_PINS_aPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "aPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 aPin__PORT == 15 && ((aPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    aPin_Write(uint8 value);
void    aPin_SetDriveMode(uint8 mode);
uint8   aPin_ReadDataReg(void);
uint8   aPin_Read(void);
void    aPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   aPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the aPin_SetDriveMode() function.
     *  @{
     */
        #define aPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define aPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define aPin_DM_RES_UP          PIN_DM_RES_UP
        #define aPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define aPin_DM_OD_LO           PIN_DM_OD_LO
        #define aPin_DM_OD_HI           PIN_DM_OD_HI
        #define aPin_DM_STRONG          PIN_DM_STRONG
        #define aPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define aPin_MASK               aPin__MASK
#define aPin_SHIFT              aPin__SHIFT
#define aPin_WIDTH              1u

/* Interrupt constants */
#if defined(aPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in aPin_SetInterruptMode() function.
     *  @{
     */
        #define aPin_INTR_NONE      (uint16)(0x0000u)
        #define aPin_INTR_RISING    (uint16)(0x0001u)
        #define aPin_INTR_FALLING   (uint16)(0x0002u)
        #define aPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define aPin_INTR_MASK      (0x01u) 
#endif /* (aPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define aPin_PS                     (* (reg8 *) aPin__PS)
/* Data Register */
#define aPin_DR                     (* (reg8 *) aPin__DR)
/* Port Number */
#define aPin_PRT_NUM                (* (reg8 *) aPin__PRT) 
/* Connect to Analog Globals */                                                  
#define aPin_AG                     (* (reg8 *) aPin__AG)                       
/* Analog MUX bux enable */
#define aPin_AMUX                   (* (reg8 *) aPin__AMUX) 
/* Bidirectional Enable */                                                        
#define aPin_BIE                    (* (reg8 *) aPin__BIE)
/* Bit-mask for Aliased Register Access */
#define aPin_BIT_MASK               (* (reg8 *) aPin__BIT_MASK)
/* Bypass Enable */
#define aPin_BYP                    (* (reg8 *) aPin__BYP)
/* Port wide control signals */                                                   
#define aPin_CTL                    (* (reg8 *) aPin__CTL)
/* Drive Modes */
#define aPin_DM0                    (* (reg8 *) aPin__DM0) 
#define aPin_DM1                    (* (reg8 *) aPin__DM1)
#define aPin_DM2                    (* (reg8 *) aPin__DM2) 
/* Input Buffer Disable Override */
#define aPin_INP_DIS                (* (reg8 *) aPin__INP_DIS)
/* LCD Common or Segment Drive */
#define aPin_LCD_COM_SEG            (* (reg8 *) aPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define aPin_LCD_EN                 (* (reg8 *) aPin__LCD_EN)
/* Slew Rate Control */
#define aPin_SLW                    (* (reg8 *) aPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define aPin_PRTDSI__CAPS_SEL       (* (reg8 *) aPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define aPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) aPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define aPin_PRTDSI__OE_SEL0        (* (reg8 *) aPin__PRTDSI__OE_SEL0) 
#define aPin_PRTDSI__OE_SEL1        (* (reg8 *) aPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define aPin_PRTDSI__OUT_SEL0       (* (reg8 *) aPin__PRTDSI__OUT_SEL0) 
#define aPin_PRTDSI__OUT_SEL1       (* (reg8 *) aPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define aPin_PRTDSI__SYNC_OUT       (* (reg8 *) aPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(aPin__SIO_CFG)
    #define aPin_SIO_HYST_EN        (* (reg8 *) aPin__SIO_HYST_EN)
    #define aPin_SIO_REG_HIFREQ     (* (reg8 *) aPin__SIO_REG_HIFREQ)
    #define aPin_SIO_CFG            (* (reg8 *) aPin__SIO_CFG)
    #define aPin_SIO_DIFF           (* (reg8 *) aPin__SIO_DIFF)
#endif /* (aPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(aPin__INTSTAT)
    #define aPin_INTSTAT            (* (reg8 *) aPin__INTSTAT)
    #define aPin_SNAP               (* (reg8 *) aPin__SNAP)
    
	#define aPin_0_INTTYPE_REG 		(* (reg8 *) aPin__0__INTTYPE)
#endif /* (aPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_aPin_H */


/* [] END OF FILE */
