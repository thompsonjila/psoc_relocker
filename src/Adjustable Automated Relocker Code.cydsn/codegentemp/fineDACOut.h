/*******************************************************************************
* File Name: fineDACOut.h  
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

#if !defined(CY_PINS_fineDACOut_H) /* Pins fineDACOut_H */
#define CY_PINS_fineDACOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fineDACOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fineDACOut__PORT == 15 && ((fineDACOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fineDACOut_Write(uint8 value);
void    fineDACOut_SetDriveMode(uint8 mode);
uint8   fineDACOut_ReadDataReg(void);
uint8   fineDACOut_Read(void);
void    fineDACOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   fineDACOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fineDACOut_SetDriveMode() function.
     *  @{
     */
        #define fineDACOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fineDACOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fineDACOut_DM_RES_UP          PIN_DM_RES_UP
        #define fineDACOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define fineDACOut_DM_OD_LO           PIN_DM_OD_LO
        #define fineDACOut_DM_OD_HI           PIN_DM_OD_HI
        #define fineDACOut_DM_STRONG          PIN_DM_STRONG
        #define fineDACOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fineDACOut_MASK               fineDACOut__MASK
#define fineDACOut_SHIFT              fineDACOut__SHIFT
#define fineDACOut_WIDTH              1u

/* Interrupt constants */
#if defined(fineDACOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fineDACOut_SetInterruptMode() function.
     *  @{
     */
        #define fineDACOut_INTR_NONE      (uint16)(0x0000u)
        #define fineDACOut_INTR_RISING    (uint16)(0x0001u)
        #define fineDACOut_INTR_FALLING   (uint16)(0x0002u)
        #define fineDACOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fineDACOut_INTR_MASK      (0x01u) 
#endif /* (fineDACOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fineDACOut_PS                     (* (reg8 *) fineDACOut__PS)
/* Data Register */
#define fineDACOut_DR                     (* (reg8 *) fineDACOut__DR)
/* Port Number */
#define fineDACOut_PRT_NUM                (* (reg8 *) fineDACOut__PRT) 
/* Connect to Analog Globals */                                                  
#define fineDACOut_AG                     (* (reg8 *) fineDACOut__AG)                       
/* Analog MUX bux enable */
#define fineDACOut_AMUX                   (* (reg8 *) fineDACOut__AMUX) 
/* Bidirectional Enable */                                                        
#define fineDACOut_BIE                    (* (reg8 *) fineDACOut__BIE)
/* Bit-mask for Aliased Register Access */
#define fineDACOut_BIT_MASK               (* (reg8 *) fineDACOut__BIT_MASK)
/* Bypass Enable */
#define fineDACOut_BYP                    (* (reg8 *) fineDACOut__BYP)
/* Port wide control signals */                                                   
#define fineDACOut_CTL                    (* (reg8 *) fineDACOut__CTL)
/* Drive Modes */
#define fineDACOut_DM0                    (* (reg8 *) fineDACOut__DM0) 
#define fineDACOut_DM1                    (* (reg8 *) fineDACOut__DM1)
#define fineDACOut_DM2                    (* (reg8 *) fineDACOut__DM2) 
/* Input Buffer Disable Override */
#define fineDACOut_INP_DIS                (* (reg8 *) fineDACOut__INP_DIS)
/* LCD Common or Segment Drive */
#define fineDACOut_LCD_COM_SEG            (* (reg8 *) fineDACOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define fineDACOut_LCD_EN                 (* (reg8 *) fineDACOut__LCD_EN)
/* Slew Rate Control */
#define fineDACOut_SLW                    (* (reg8 *) fineDACOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fineDACOut_PRTDSI__CAPS_SEL       (* (reg8 *) fineDACOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fineDACOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fineDACOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fineDACOut_PRTDSI__OE_SEL0        (* (reg8 *) fineDACOut__PRTDSI__OE_SEL0) 
#define fineDACOut_PRTDSI__OE_SEL1        (* (reg8 *) fineDACOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fineDACOut_PRTDSI__OUT_SEL0       (* (reg8 *) fineDACOut__PRTDSI__OUT_SEL0) 
#define fineDACOut_PRTDSI__OUT_SEL1       (* (reg8 *) fineDACOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fineDACOut_PRTDSI__SYNC_OUT       (* (reg8 *) fineDACOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fineDACOut__SIO_CFG)
    #define fineDACOut_SIO_HYST_EN        (* (reg8 *) fineDACOut__SIO_HYST_EN)
    #define fineDACOut_SIO_REG_HIFREQ     (* (reg8 *) fineDACOut__SIO_REG_HIFREQ)
    #define fineDACOut_SIO_CFG            (* (reg8 *) fineDACOut__SIO_CFG)
    #define fineDACOut_SIO_DIFF           (* (reg8 *) fineDACOut__SIO_DIFF)
#endif /* (fineDACOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(fineDACOut__INTSTAT)
    #define fineDACOut_INTSTAT            (* (reg8 *) fineDACOut__INTSTAT)
    #define fineDACOut_SNAP               (* (reg8 *) fineDACOut__SNAP)
    
	#define fineDACOut_0_INTTYPE_REG 		(* (reg8 *) fineDACOut__0__INTTYPE)
#endif /* (fineDACOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fineDACOut_H */


/* [] END OF FILE */
