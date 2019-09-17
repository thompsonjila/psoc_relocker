/*******************************************************************************
* File Name: checkLight.h  
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

#if !defined(CY_PINS_checkLight_H) /* Pins checkLight_H */
#define CY_PINS_checkLight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "checkLight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 checkLight__PORT == 15 && ((checkLight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    checkLight_Write(uint8 value);
void    checkLight_SetDriveMode(uint8 mode);
uint8   checkLight_ReadDataReg(void);
uint8   checkLight_Read(void);
void    checkLight_SetInterruptMode(uint16 position, uint16 mode);
uint8   checkLight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the checkLight_SetDriveMode() function.
     *  @{
     */
        #define checkLight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define checkLight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define checkLight_DM_RES_UP          PIN_DM_RES_UP
        #define checkLight_DM_RES_DWN         PIN_DM_RES_DWN
        #define checkLight_DM_OD_LO           PIN_DM_OD_LO
        #define checkLight_DM_OD_HI           PIN_DM_OD_HI
        #define checkLight_DM_STRONG          PIN_DM_STRONG
        #define checkLight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define checkLight_MASK               checkLight__MASK
#define checkLight_SHIFT              checkLight__SHIFT
#define checkLight_WIDTH              1u

/* Interrupt constants */
#if defined(checkLight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in checkLight_SetInterruptMode() function.
     *  @{
     */
        #define checkLight_INTR_NONE      (uint16)(0x0000u)
        #define checkLight_INTR_RISING    (uint16)(0x0001u)
        #define checkLight_INTR_FALLING   (uint16)(0x0002u)
        #define checkLight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define checkLight_INTR_MASK      (0x01u) 
#endif /* (checkLight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define checkLight_PS                     (* (reg8 *) checkLight__PS)
/* Data Register */
#define checkLight_DR                     (* (reg8 *) checkLight__DR)
/* Port Number */
#define checkLight_PRT_NUM                (* (reg8 *) checkLight__PRT) 
/* Connect to Analog Globals */                                                  
#define checkLight_AG                     (* (reg8 *) checkLight__AG)                       
/* Analog MUX bux enable */
#define checkLight_AMUX                   (* (reg8 *) checkLight__AMUX) 
/* Bidirectional Enable */                                                        
#define checkLight_BIE                    (* (reg8 *) checkLight__BIE)
/* Bit-mask for Aliased Register Access */
#define checkLight_BIT_MASK               (* (reg8 *) checkLight__BIT_MASK)
/* Bypass Enable */
#define checkLight_BYP                    (* (reg8 *) checkLight__BYP)
/* Port wide control signals */                                                   
#define checkLight_CTL                    (* (reg8 *) checkLight__CTL)
/* Drive Modes */
#define checkLight_DM0                    (* (reg8 *) checkLight__DM0) 
#define checkLight_DM1                    (* (reg8 *) checkLight__DM1)
#define checkLight_DM2                    (* (reg8 *) checkLight__DM2) 
/* Input Buffer Disable Override */
#define checkLight_INP_DIS                (* (reg8 *) checkLight__INP_DIS)
/* LCD Common or Segment Drive */
#define checkLight_LCD_COM_SEG            (* (reg8 *) checkLight__LCD_COM_SEG)
/* Enable Segment LCD */
#define checkLight_LCD_EN                 (* (reg8 *) checkLight__LCD_EN)
/* Slew Rate Control */
#define checkLight_SLW                    (* (reg8 *) checkLight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define checkLight_PRTDSI__CAPS_SEL       (* (reg8 *) checkLight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define checkLight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) checkLight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define checkLight_PRTDSI__OE_SEL0        (* (reg8 *) checkLight__PRTDSI__OE_SEL0) 
#define checkLight_PRTDSI__OE_SEL1        (* (reg8 *) checkLight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define checkLight_PRTDSI__OUT_SEL0       (* (reg8 *) checkLight__PRTDSI__OUT_SEL0) 
#define checkLight_PRTDSI__OUT_SEL1       (* (reg8 *) checkLight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define checkLight_PRTDSI__SYNC_OUT       (* (reg8 *) checkLight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(checkLight__SIO_CFG)
    #define checkLight_SIO_HYST_EN        (* (reg8 *) checkLight__SIO_HYST_EN)
    #define checkLight_SIO_REG_HIFREQ     (* (reg8 *) checkLight__SIO_REG_HIFREQ)
    #define checkLight_SIO_CFG            (* (reg8 *) checkLight__SIO_CFG)
    #define checkLight_SIO_DIFF           (* (reg8 *) checkLight__SIO_DIFF)
#endif /* (checkLight__SIO_CFG) */

/* Interrupt Registers */
#if defined(checkLight__INTSTAT)
    #define checkLight_INTSTAT            (* (reg8 *) checkLight__INTSTAT)
    #define checkLight_SNAP               (* (reg8 *) checkLight__SNAP)
    
	#define checkLight_0_INTTYPE_REG 		(* (reg8 *) checkLight__0__INTTYPE)
#endif /* (checkLight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_checkLight_H */


/* [] END OF FILE */
