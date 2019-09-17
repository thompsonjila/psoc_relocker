/*******************************************************************************
* File Name: errMonPin.h  
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

#if !defined(CY_PINS_errMonPin_H) /* Pins errMonPin_H */
#define CY_PINS_errMonPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "errMonPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 errMonPin__PORT == 15 && ((errMonPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    errMonPin_Write(uint8 value);
void    errMonPin_SetDriveMode(uint8 mode);
uint8   errMonPin_ReadDataReg(void);
uint8   errMonPin_Read(void);
void    errMonPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   errMonPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the errMonPin_SetDriveMode() function.
     *  @{
     */
        #define errMonPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define errMonPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define errMonPin_DM_RES_UP          PIN_DM_RES_UP
        #define errMonPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define errMonPin_DM_OD_LO           PIN_DM_OD_LO
        #define errMonPin_DM_OD_HI           PIN_DM_OD_HI
        #define errMonPin_DM_STRONG          PIN_DM_STRONG
        #define errMonPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define errMonPin_MASK               errMonPin__MASK
#define errMonPin_SHIFT              errMonPin__SHIFT
#define errMonPin_WIDTH              1u

/* Interrupt constants */
#if defined(errMonPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in errMonPin_SetInterruptMode() function.
     *  @{
     */
        #define errMonPin_INTR_NONE      (uint16)(0x0000u)
        #define errMonPin_INTR_RISING    (uint16)(0x0001u)
        #define errMonPin_INTR_FALLING   (uint16)(0x0002u)
        #define errMonPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define errMonPin_INTR_MASK      (0x01u) 
#endif /* (errMonPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define errMonPin_PS                     (* (reg8 *) errMonPin__PS)
/* Data Register */
#define errMonPin_DR                     (* (reg8 *) errMonPin__DR)
/* Port Number */
#define errMonPin_PRT_NUM                (* (reg8 *) errMonPin__PRT) 
/* Connect to Analog Globals */                                                  
#define errMonPin_AG                     (* (reg8 *) errMonPin__AG)                       
/* Analog MUX bux enable */
#define errMonPin_AMUX                   (* (reg8 *) errMonPin__AMUX) 
/* Bidirectional Enable */                                                        
#define errMonPin_BIE                    (* (reg8 *) errMonPin__BIE)
/* Bit-mask for Aliased Register Access */
#define errMonPin_BIT_MASK               (* (reg8 *) errMonPin__BIT_MASK)
/* Bypass Enable */
#define errMonPin_BYP                    (* (reg8 *) errMonPin__BYP)
/* Port wide control signals */                                                   
#define errMonPin_CTL                    (* (reg8 *) errMonPin__CTL)
/* Drive Modes */
#define errMonPin_DM0                    (* (reg8 *) errMonPin__DM0) 
#define errMonPin_DM1                    (* (reg8 *) errMonPin__DM1)
#define errMonPin_DM2                    (* (reg8 *) errMonPin__DM2) 
/* Input Buffer Disable Override */
#define errMonPin_INP_DIS                (* (reg8 *) errMonPin__INP_DIS)
/* LCD Common or Segment Drive */
#define errMonPin_LCD_COM_SEG            (* (reg8 *) errMonPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define errMonPin_LCD_EN                 (* (reg8 *) errMonPin__LCD_EN)
/* Slew Rate Control */
#define errMonPin_SLW                    (* (reg8 *) errMonPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define errMonPin_PRTDSI__CAPS_SEL       (* (reg8 *) errMonPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define errMonPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) errMonPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define errMonPin_PRTDSI__OE_SEL0        (* (reg8 *) errMonPin__PRTDSI__OE_SEL0) 
#define errMonPin_PRTDSI__OE_SEL1        (* (reg8 *) errMonPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define errMonPin_PRTDSI__OUT_SEL0       (* (reg8 *) errMonPin__PRTDSI__OUT_SEL0) 
#define errMonPin_PRTDSI__OUT_SEL1       (* (reg8 *) errMonPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define errMonPin_PRTDSI__SYNC_OUT       (* (reg8 *) errMonPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(errMonPin__SIO_CFG)
    #define errMonPin_SIO_HYST_EN        (* (reg8 *) errMonPin__SIO_HYST_EN)
    #define errMonPin_SIO_REG_HIFREQ     (* (reg8 *) errMonPin__SIO_REG_HIFREQ)
    #define errMonPin_SIO_CFG            (* (reg8 *) errMonPin__SIO_CFG)
    #define errMonPin_SIO_DIFF           (* (reg8 *) errMonPin__SIO_DIFF)
#endif /* (errMonPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(errMonPin__INTSTAT)
    #define errMonPin_INTSTAT            (* (reg8 *) errMonPin__INTSTAT)
    #define errMonPin_SNAP               (* (reg8 *) errMonPin__SNAP)
    
	#define errMonPin_0_INTTYPE_REG 		(* (reg8 *) errMonPin__0__INTTYPE)
#endif /* (errMonPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_errMonPin_H */


/* [] END OF FILE */
