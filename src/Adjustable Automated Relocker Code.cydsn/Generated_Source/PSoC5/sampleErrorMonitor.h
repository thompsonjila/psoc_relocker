/*******************************************************************************
* File Name: sampleErrorMonitor.h  
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

#if !defined(CY_PINS_sampleErrorMonitor_H) /* Pins sampleErrorMonitor_H */
#define CY_PINS_sampleErrorMonitor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sampleErrorMonitor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sampleErrorMonitor__PORT == 15 && ((sampleErrorMonitor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sampleErrorMonitor_Write(uint8 value);
void    sampleErrorMonitor_SetDriveMode(uint8 mode);
uint8   sampleErrorMonitor_ReadDataReg(void);
uint8   sampleErrorMonitor_Read(void);
void    sampleErrorMonitor_SetInterruptMode(uint16 position, uint16 mode);
uint8   sampleErrorMonitor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sampleErrorMonitor_SetDriveMode() function.
     *  @{
     */
        #define sampleErrorMonitor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sampleErrorMonitor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sampleErrorMonitor_DM_RES_UP          PIN_DM_RES_UP
        #define sampleErrorMonitor_DM_RES_DWN         PIN_DM_RES_DWN
        #define sampleErrorMonitor_DM_OD_LO           PIN_DM_OD_LO
        #define sampleErrorMonitor_DM_OD_HI           PIN_DM_OD_HI
        #define sampleErrorMonitor_DM_STRONG          PIN_DM_STRONG
        #define sampleErrorMonitor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sampleErrorMonitor_MASK               sampleErrorMonitor__MASK
#define sampleErrorMonitor_SHIFT              sampleErrorMonitor__SHIFT
#define sampleErrorMonitor_WIDTH              1u

/* Interrupt constants */
#if defined(sampleErrorMonitor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sampleErrorMonitor_SetInterruptMode() function.
     *  @{
     */
        #define sampleErrorMonitor_INTR_NONE      (uint16)(0x0000u)
        #define sampleErrorMonitor_INTR_RISING    (uint16)(0x0001u)
        #define sampleErrorMonitor_INTR_FALLING   (uint16)(0x0002u)
        #define sampleErrorMonitor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sampleErrorMonitor_INTR_MASK      (0x01u) 
#endif /* (sampleErrorMonitor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sampleErrorMonitor_PS                     (* (reg8 *) sampleErrorMonitor__PS)
/* Data Register */
#define sampleErrorMonitor_DR                     (* (reg8 *) sampleErrorMonitor__DR)
/* Port Number */
#define sampleErrorMonitor_PRT_NUM                (* (reg8 *) sampleErrorMonitor__PRT) 
/* Connect to Analog Globals */                                                  
#define sampleErrorMonitor_AG                     (* (reg8 *) sampleErrorMonitor__AG)                       
/* Analog MUX bux enable */
#define sampleErrorMonitor_AMUX                   (* (reg8 *) sampleErrorMonitor__AMUX) 
/* Bidirectional Enable */                                                        
#define sampleErrorMonitor_BIE                    (* (reg8 *) sampleErrorMonitor__BIE)
/* Bit-mask for Aliased Register Access */
#define sampleErrorMonitor_BIT_MASK               (* (reg8 *) sampleErrorMonitor__BIT_MASK)
/* Bypass Enable */
#define sampleErrorMonitor_BYP                    (* (reg8 *) sampleErrorMonitor__BYP)
/* Port wide control signals */                                                   
#define sampleErrorMonitor_CTL                    (* (reg8 *) sampleErrorMonitor__CTL)
/* Drive Modes */
#define sampleErrorMonitor_DM0                    (* (reg8 *) sampleErrorMonitor__DM0) 
#define sampleErrorMonitor_DM1                    (* (reg8 *) sampleErrorMonitor__DM1)
#define sampleErrorMonitor_DM2                    (* (reg8 *) sampleErrorMonitor__DM2) 
/* Input Buffer Disable Override */
#define sampleErrorMonitor_INP_DIS                (* (reg8 *) sampleErrorMonitor__INP_DIS)
/* LCD Common or Segment Drive */
#define sampleErrorMonitor_LCD_COM_SEG            (* (reg8 *) sampleErrorMonitor__LCD_COM_SEG)
/* Enable Segment LCD */
#define sampleErrorMonitor_LCD_EN                 (* (reg8 *) sampleErrorMonitor__LCD_EN)
/* Slew Rate Control */
#define sampleErrorMonitor_SLW                    (* (reg8 *) sampleErrorMonitor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sampleErrorMonitor_PRTDSI__CAPS_SEL       (* (reg8 *) sampleErrorMonitor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sampleErrorMonitor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sampleErrorMonitor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sampleErrorMonitor_PRTDSI__OE_SEL0        (* (reg8 *) sampleErrorMonitor__PRTDSI__OE_SEL0) 
#define sampleErrorMonitor_PRTDSI__OE_SEL1        (* (reg8 *) sampleErrorMonitor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sampleErrorMonitor_PRTDSI__OUT_SEL0       (* (reg8 *) sampleErrorMonitor__PRTDSI__OUT_SEL0) 
#define sampleErrorMonitor_PRTDSI__OUT_SEL1       (* (reg8 *) sampleErrorMonitor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sampleErrorMonitor_PRTDSI__SYNC_OUT       (* (reg8 *) sampleErrorMonitor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sampleErrorMonitor__SIO_CFG)
    #define sampleErrorMonitor_SIO_HYST_EN        (* (reg8 *) sampleErrorMonitor__SIO_HYST_EN)
    #define sampleErrorMonitor_SIO_REG_HIFREQ     (* (reg8 *) sampleErrorMonitor__SIO_REG_HIFREQ)
    #define sampleErrorMonitor_SIO_CFG            (* (reg8 *) sampleErrorMonitor__SIO_CFG)
    #define sampleErrorMonitor_SIO_DIFF           (* (reg8 *) sampleErrorMonitor__SIO_DIFF)
#endif /* (sampleErrorMonitor__SIO_CFG) */

/* Interrupt Registers */
#if defined(sampleErrorMonitor__INTSTAT)
    #define sampleErrorMonitor_INTSTAT            (* (reg8 *) sampleErrorMonitor__INTSTAT)
    #define sampleErrorMonitor_SNAP               (* (reg8 *) sampleErrorMonitor__SNAP)
    
	#define sampleErrorMonitor_0_INTTYPE_REG 		(* (reg8 *) sampleErrorMonitor__0__INTTYPE)
#endif /* (sampleErrorMonitor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sampleErrorMonitor_H */


/* [] END OF FILE */
