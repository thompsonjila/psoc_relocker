/*******************************************************************************
* File Name: coarseDACOut.h  
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

#if !defined(CY_PINS_coarseDACOut_H) /* Pins coarseDACOut_H */
#define CY_PINS_coarseDACOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "coarseDACOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 coarseDACOut__PORT == 15 && ((coarseDACOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    coarseDACOut_Write(uint8 value);
void    coarseDACOut_SetDriveMode(uint8 mode);
uint8   coarseDACOut_ReadDataReg(void);
uint8   coarseDACOut_Read(void);
void    coarseDACOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   coarseDACOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the coarseDACOut_SetDriveMode() function.
     *  @{
     */
        #define coarseDACOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define coarseDACOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define coarseDACOut_DM_RES_UP          PIN_DM_RES_UP
        #define coarseDACOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define coarseDACOut_DM_OD_LO           PIN_DM_OD_LO
        #define coarseDACOut_DM_OD_HI           PIN_DM_OD_HI
        #define coarseDACOut_DM_STRONG          PIN_DM_STRONG
        #define coarseDACOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define coarseDACOut_MASK               coarseDACOut__MASK
#define coarseDACOut_SHIFT              coarseDACOut__SHIFT
#define coarseDACOut_WIDTH              1u

/* Interrupt constants */
#if defined(coarseDACOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in coarseDACOut_SetInterruptMode() function.
     *  @{
     */
        #define coarseDACOut_INTR_NONE      (uint16)(0x0000u)
        #define coarseDACOut_INTR_RISING    (uint16)(0x0001u)
        #define coarseDACOut_INTR_FALLING   (uint16)(0x0002u)
        #define coarseDACOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define coarseDACOut_INTR_MASK      (0x01u) 
#endif /* (coarseDACOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define coarseDACOut_PS                     (* (reg8 *) coarseDACOut__PS)
/* Data Register */
#define coarseDACOut_DR                     (* (reg8 *) coarseDACOut__DR)
/* Port Number */
#define coarseDACOut_PRT_NUM                (* (reg8 *) coarseDACOut__PRT) 
/* Connect to Analog Globals */                                                  
#define coarseDACOut_AG                     (* (reg8 *) coarseDACOut__AG)                       
/* Analog MUX bux enable */
#define coarseDACOut_AMUX                   (* (reg8 *) coarseDACOut__AMUX) 
/* Bidirectional Enable */                                                        
#define coarseDACOut_BIE                    (* (reg8 *) coarseDACOut__BIE)
/* Bit-mask for Aliased Register Access */
#define coarseDACOut_BIT_MASK               (* (reg8 *) coarseDACOut__BIT_MASK)
/* Bypass Enable */
#define coarseDACOut_BYP                    (* (reg8 *) coarseDACOut__BYP)
/* Port wide control signals */                                                   
#define coarseDACOut_CTL                    (* (reg8 *) coarseDACOut__CTL)
/* Drive Modes */
#define coarseDACOut_DM0                    (* (reg8 *) coarseDACOut__DM0) 
#define coarseDACOut_DM1                    (* (reg8 *) coarseDACOut__DM1)
#define coarseDACOut_DM2                    (* (reg8 *) coarseDACOut__DM2) 
/* Input Buffer Disable Override */
#define coarseDACOut_INP_DIS                (* (reg8 *) coarseDACOut__INP_DIS)
/* LCD Common or Segment Drive */
#define coarseDACOut_LCD_COM_SEG            (* (reg8 *) coarseDACOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define coarseDACOut_LCD_EN                 (* (reg8 *) coarseDACOut__LCD_EN)
/* Slew Rate Control */
#define coarseDACOut_SLW                    (* (reg8 *) coarseDACOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define coarseDACOut_PRTDSI__CAPS_SEL       (* (reg8 *) coarseDACOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define coarseDACOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) coarseDACOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define coarseDACOut_PRTDSI__OE_SEL0        (* (reg8 *) coarseDACOut__PRTDSI__OE_SEL0) 
#define coarseDACOut_PRTDSI__OE_SEL1        (* (reg8 *) coarseDACOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define coarseDACOut_PRTDSI__OUT_SEL0       (* (reg8 *) coarseDACOut__PRTDSI__OUT_SEL0) 
#define coarseDACOut_PRTDSI__OUT_SEL1       (* (reg8 *) coarseDACOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define coarseDACOut_PRTDSI__SYNC_OUT       (* (reg8 *) coarseDACOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(coarseDACOut__SIO_CFG)
    #define coarseDACOut_SIO_HYST_EN        (* (reg8 *) coarseDACOut__SIO_HYST_EN)
    #define coarseDACOut_SIO_REG_HIFREQ     (* (reg8 *) coarseDACOut__SIO_REG_HIFREQ)
    #define coarseDACOut_SIO_CFG            (* (reg8 *) coarseDACOut__SIO_CFG)
    #define coarseDACOut_SIO_DIFF           (* (reg8 *) coarseDACOut__SIO_DIFF)
#endif /* (coarseDACOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(coarseDACOut__INTSTAT)
    #define coarseDACOut_INTSTAT            (* (reg8 *) coarseDACOut__INTSTAT)
    #define coarseDACOut_SNAP               (* (reg8 *) coarseDACOut__SNAP)
    
	#define coarseDACOut_0_INTTYPE_REG 		(* (reg8 *) coarseDACOut__0__INTTYPE)
#endif /* (coarseDACOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_coarseDACOut_H */


/* [] END OF FILE */
