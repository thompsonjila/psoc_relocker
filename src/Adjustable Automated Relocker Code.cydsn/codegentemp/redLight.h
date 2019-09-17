/*******************************************************************************
* File Name: redLight.h  
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

#if !defined(CY_PINS_redLight_H) /* Pins redLight_H */
#define CY_PINS_redLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "redLight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 redLight__PORT == 15 && ((redLight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    redLight_Write(uint8 value);
void    redLight_SetDriveMode(uint8 mode);
uint8   redLight_ReadDataReg(void);
uint8   redLight_Read(void);
void    redLight_SetInterruptMode(uint16 position, uint16 mode);
uint8   redLight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the redLight_SetDriveMode() function.
     *  @{
     */
        #define redLight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define redLight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define redLight_DM_RES_UP          PIN_DM_RES_UP
        #define redLight_DM_RES_DWN         PIN_DM_RES_DWN
        #define redLight_DM_OD_LO           PIN_DM_OD_LO
        #define redLight_DM_OD_HI           PIN_DM_OD_HI
        #define redLight_DM_STRONG          PIN_DM_STRONG
        #define redLight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define redLight_MASK               redLight__MASK
#define redLight_SHIFT              redLight__SHIFT
#define redLight_WIDTH              1u

/* Interrupt constants */
#if defined(redLight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in redLight_SetInterruptMode() function.
     *  @{
     */
        #define redLight_INTR_NONE      (uint16)(0x0000u)
        #define redLight_INTR_RISING    (uint16)(0x0001u)
        #define redLight_INTR_FALLING   (uint16)(0x0002u)
        #define redLight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define redLight_INTR_MASK      (0x01u) 
#endif /* (redLight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define redLight_PS                     (* (reg8 *) redLight__PS)
/* Data Register */
#define redLight_DR                     (* (reg8 *) redLight__DR)
/* Port Number */
#define redLight_PRT_NUM                (* (reg8 *) redLight__PRT) 
/* Connect to Analog Globals */                                                  
#define redLight_AG                     (* (reg8 *) redLight__AG)                       
/* Analog MUX bux enable */
#define redLight_AMUX                   (* (reg8 *) redLight__AMUX) 
/* Bidirectional Enable */                                                        
#define redLight_BIE                    (* (reg8 *) redLight__BIE)
/* Bit-mask for Aliased Register Access */
#define redLight_BIT_MASK               (* (reg8 *) redLight__BIT_MASK)
/* Bypass Enable */
#define redLight_BYP                    (* (reg8 *) redLight__BYP)
/* Port wide control signals */                                                   
#define redLight_CTL                    (* (reg8 *) redLight__CTL)
/* Drive Modes */
#define redLight_DM0                    (* (reg8 *) redLight__DM0) 
#define redLight_DM1                    (* (reg8 *) redLight__DM1)
#define redLight_DM2                    (* (reg8 *) redLight__DM2) 
/* Input Buffer Disable Override */
#define redLight_INP_DIS                (* (reg8 *) redLight__INP_DIS)
/* LCD Common or Segment Drive */
#define redLight_LCD_COM_SEG            (* (reg8 *) redLight__LCD_COM_SEG)
/* Enable Segment LCD */
#define redLight_LCD_EN                 (* (reg8 *) redLight__LCD_EN)
/* Slew Rate Control */
#define redLight_SLW                    (* (reg8 *) redLight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define redLight_PRTDSI__CAPS_SEL       (* (reg8 *) redLight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define redLight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) redLight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define redLight_PRTDSI__OE_SEL0        (* (reg8 *) redLight__PRTDSI__OE_SEL0) 
#define redLight_PRTDSI__OE_SEL1        (* (reg8 *) redLight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define redLight_PRTDSI__OUT_SEL0       (* (reg8 *) redLight__PRTDSI__OUT_SEL0) 
#define redLight_PRTDSI__OUT_SEL1       (* (reg8 *) redLight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define redLight_PRTDSI__SYNC_OUT       (* (reg8 *) redLight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(redLight__SIO_CFG)
    #define redLight_SIO_HYST_EN        (* (reg8 *) redLight__SIO_HYST_EN)
    #define redLight_SIO_REG_HIFREQ     (* (reg8 *) redLight__SIO_REG_HIFREQ)
    #define redLight_SIO_CFG            (* (reg8 *) redLight__SIO_CFG)
    #define redLight_SIO_DIFF           (* (reg8 *) redLight__SIO_DIFF)
#endif /* (redLight__SIO_CFG) */

/* Interrupt Registers */
#if defined(redLight__INTSTAT)
    #define redLight_INTSTAT            (* (reg8 *) redLight__INTSTAT)
    #define redLight_SNAP               (* (reg8 *) redLight__SNAP)
    
	#define redLight_0_INTTYPE_REG 		(* (reg8 *) redLight__0__INTTYPE)
#endif /* (redLight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_redLight_H */


/* [] END OF FILE */
