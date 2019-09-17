/*******************************************************************************
* File Name: bPin.h  
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

#if !defined(CY_PINS_bPin_H) /* Pins bPin_H */
#define CY_PINS_bPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "bPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 bPin__PORT == 15 && ((bPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    bPin_Write(uint8 value);
void    bPin_SetDriveMode(uint8 mode);
uint8   bPin_ReadDataReg(void);
uint8   bPin_Read(void);
void    bPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   bPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the bPin_SetDriveMode() function.
     *  @{
     */
        #define bPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define bPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define bPin_DM_RES_UP          PIN_DM_RES_UP
        #define bPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define bPin_DM_OD_LO           PIN_DM_OD_LO
        #define bPin_DM_OD_HI           PIN_DM_OD_HI
        #define bPin_DM_STRONG          PIN_DM_STRONG
        #define bPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define bPin_MASK               bPin__MASK
#define bPin_SHIFT              bPin__SHIFT
#define bPin_WIDTH              1u

/* Interrupt constants */
#if defined(bPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in bPin_SetInterruptMode() function.
     *  @{
     */
        #define bPin_INTR_NONE      (uint16)(0x0000u)
        #define bPin_INTR_RISING    (uint16)(0x0001u)
        #define bPin_INTR_FALLING   (uint16)(0x0002u)
        #define bPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define bPin_INTR_MASK      (0x01u) 
#endif /* (bPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define bPin_PS                     (* (reg8 *) bPin__PS)
/* Data Register */
#define bPin_DR                     (* (reg8 *) bPin__DR)
/* Port Number */
#define bPin_PRT_NUM                (* (reg8 *) bPin__PRT) 
/* Connect to Analog Globals */                                                  
#define bPin_AG                     (* (reg8 *) bPin__AG)                       
/* Analog MUX bux enable */
#define bPin_AMUX                   (* (reg8 *) bPin__AMUX) 
/* Bidirectional Enable */                                                        
#define bPin_BIE                    (* (reg8 *) bPin__BIE)
/* Bit-mask for Aliased Register Access */
#define bPin_BIT_MASK               (* (reg8 *) bPin__BIT_MASK)
/* Bypass Enable */
#define bPin_BYP                    (* (reg8 *) bPin__BYP)
/* Port wide control signals */                                                   
#define bPin_CTL                    (* (reg8 *) bPin__CTL)
/* Drive Modes */
#define bPin_DM0                    (* (reg8 *) bPin__DM0) 
#define bPin_DM1                    (* (reg8 *) bPin__DM1)
#define bPin_DM2                    (* (reg8 *) bPin__DM2) 
/* Input Buffer Disable Override */
#define bPin_INP_DIS                (* (reg8 *) bPin__INP_DIS)
/* LCD Common or Segment Drive */
#define bPin_LCD_COM_SEG            (* (reg8 *) bPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define bPin_LCD_EN                 (* (reg8 *) bPin__LCD_EN)
/* Slew Rate Control */
#define bPin_SLW                    (* (reg8 *) bPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define bPin_PRTDSI__CAPS_SEL       (* (reg8 *) bPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define bPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) bPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define bPin_PRTDSI__OE_SEL0        (* (reg8 *) bPin__PRTDSI__OE_SEL0) 
#define bPin_PRTDSI__OE_SEL1        (* (reg8 *) bPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define bPin_PRTDSI__OUT_SEL0       (* (reg8 *) bPin__PRTDSI__OUT_SEL0) 
#define bPin_PRTDSI__OUT_SEL1       (* (reg8 *) bPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define bPin_PRTDSI__SYNC_OUT       (* (reg8 *) bPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(bPin__SIO_CFG)
    #define bPin_SIO_HYST_EN        (* (reg8 *) bPin__SIO_HYST_EN)
    #define bPin_SIO_REG_HIFREQ     (* (reg8 *) bPin__SIO_REG_HIFREQ)
    #define bPin_SIO_CFG            (* (reg8 *) bPin__SIO_CFG)
    #define bPin_SIO_DIFF           (* (reg8 *) bPin__SIO_DIFF)
#endif /* (bPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(bPin__INTSTAT)
    #define bPin_INTSTAT            (* (reg8 *) bPin__INTSTAT)
    #define bPin_SNAP               (* (reg8 *) bPin__SNAP)
    
	#define bPin_0_INTTYPE_REG 		(* (reg8 *) bPin__0__INTTYPE)
#endif /* (bPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_bPin_H */


/* [] END OF FILE */
