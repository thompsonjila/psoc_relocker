/*******************************************************************************
* File Name: courseMCOut.h  
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

#if !defined(CY_PINS_courseMCOut_H) /* Pins courseMCOut_H */
#define CY_PINS_courseMCOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "courseMCOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 courseMCOut__PORT == 15 && ((courseMCOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    courseMCOut_Write(uint8 value);
void    courseMCOut_SetDriveMode(uint8 mode);
uint8   courseMCOut_ReadDataReg(void);
uint8   courseMCOut_Read(void);
void    courseMCOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   courseMCOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the courseMCOut_SetDriveMode() function.
     *  @{
     */
        #define courseMCOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define courseMCOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define courseMCOut_DM_RES_UP          PIN_DM_RES_UP
        #define courseMCOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define courseMCOut_DM_OD_LO           PIN_DM_OD_LO
        #define courseMCOut_DM_OD_HI           PIN_DM_OD_HI
        #define courseMCOut_DM_STRONG          PIN_DM_STRONG
        #define courseMCOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define courseMCOut_MASK               courseMCOut__MASK
#define courseMCOut_SHIFT              courseMCOut__SHIFT
#define courseMCOut_WIDTH              1u

/* Interrupt constants */
#if defined(courseMCOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in courseMCOut_SetInterruptMode() function.
     *  @{
     */
        #define courseMCOut_INTR_NONE      (uint16)(0x0000u)
        #define courseMCOut_INTR_RISING    (uint16)(0x0001u)
        #define courseMCOut_INTR_FALLING   (uint16)(0x0002u)
        #define courseMCOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define courseMCOut_INTR_MASK      (0x01u) 
#endif /* (courseMCOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define courseMCOut_PS                     (* (reg8 *) courseMCOut__PS)
/* Data Register */
#define courseMCOut_DR                     (* (reg8 *) courseMCOut__DR)
/* Port Number */
#define courseMCOut_PRT_NUM                (* (reg8 *) courseMCOut__PRT) 
/* Connect to Analog Globals */                                                  
#define courseMCOut_AG                     (* (reg8 *) courseMCOut__AG)                       
/* Analog MUX bux enable */
#define courseMCOut_AMUX                   (* (reg8 *) courseMCOut__AMUX) 
/* Bidirectional Enable */                                                        
#define courseMCOut_BIE                    (* (reg8 *) courseMCOut__BIE)
/* Bit-mask for Aliased Register Access */
#define courseMCOut_BIT_MASK               (* (reg8 *) courseMCOut__BIT_MASK)
/* Bypass Enable */
#define courseMCOut_BYP                    (* (reg8 *) courseMCOut__BYP)
/* Port wide control signals */                                                   
#define courseMCOut_CTL                    (* (reg8 *) courseMCOut__CTL)
/* Drive Modes */
#define courseMCOut_DM0                    (* (reg8 *) courseMCOut__DM0) 
#define courseMCOut_DM1                    (* (reg8 *) courseMCOut__DM1)
#define courseMCOut_DM2                    (* (reg8 *) courseMCOut__DM2) 
/* Input Buffer Disable Override */
#define courseMCOut_INP_DIS                (* (reg8 *) courseMCOut__INP_DIS)
/* LCD Common or Segment Drive */
#define courseMCOut_LCD_COM_SEG            (* (reg8 *) courseMCOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define courseMCOut_LCD_EN                 (* (reg8 *) courseMCOut__LCD_EN)
/* Slew Rate Control */
#define courseMCOut_SLW                    (* (reg8 *) courseMCOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define courseMCOut_PRTDSI__CAPS_SEL       (* (reg8 *) courseMCOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define courseMCOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) courseMCOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define courseMCOut_PRTDSI__OE_SEL0        (* (reg8 *) courseMCOut__PRTDSI__OE_SEL0) 
#define courseMCOut_PRTDSI__OE_SEL1        (* (reg8 *) courseMCOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define courseMCOut_PRTDSI__OUT_SEL0       (* (reg8 *) courseMCOut__PRTDSI__OUT_SEL0) 
#define courseMCOut_PRTDSI__OUT_SEL1       (* (reg8 *) courseMCOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define courseMCOut_PRTDSI__SYNC_OUT       (* (reg8 *) courseMCOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(courseMCOut__SIO_CFG)
    #define courseMCOut_SIO_HYST_EN        (* (reg8 *) courseMCOut__SIO_HYST_EN)
    #define courseMCOut_SIO_REG_HIFREQ     (* (reg8 *) courseMCOut__SIO_REG_HIFREQ)
    #define courseMCOut_SIO_CFG            (* (reg8 *) courseMCOut__SIO_CFG)
    #define courseMCOut_SIO_DIFF           (* (reg8 *) courseMCOut__SIO_DIFF)
#endif /* (courseMCOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(courseMCOut__INTSTAT)
    #define courseMCOut_INTSTAT            (* (reg8 *) courseMCOut__INTSTAT)
    #define courseMCOut_SNAP               (* (reg8 *) courseMCOut__SNAP)
    
	#define courseMCOut_0_INTTYPE_REG 		(* (reg8 *) courseMCOut__0__INTTYPE)
#endif /* (courseMCOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_courseMCOut_H */


/* [] END OF FILE */
