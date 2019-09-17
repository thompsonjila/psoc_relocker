/*******************************************************************************
* File Name: fineMPOut.h  
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

#if !defined(CY_PINS_fineMPOut_H) /* Pins fineMPOut_H */
#define CY_PINS_fineMPOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fineMPOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fineMPOut__PORT == 15 && ((fineMPOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fineMPOut_Write(uint8 value);
void    fineMPOut_SetDriveMode(uint8 mode);
uint8   fineMPOut_ReadDataReg(void);
uint8   fineMPOut_Read(void);
void    fineMPOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   fineMPOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fineMPOut_SetDriveMode() function.
     *  @{
     */
        #define fineMPOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fineMPOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fineMPOut_DM_RES_UP          PIN_DM_RES_UP
        #define fineMPOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define fineMPOut_DM_OD_LO           PIN_DM_OD_LO
        #define fineMPOut_DM_OD_HI           PIN_DM_OD_HI
        #define fineMPOut_DM_STRONG          PIN_DM_STRONG
        #define fineMPOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fineMPOut_MASK               fineMPOut__MASK
#define fineMPOut_SHIFT              fineMPOut__SHIFT
#define fineMPOut_WIDTH              1u

/* Interrupt constants */
#if defined(fineMPOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fineMPOut_SetInterruptMode() function.
     *  @{
     */
        #define fineMPOut_INTR_NONE      (uint16)(0x0000u)
        #define fineMPOut_INTR_RISING    (uint16)(0x0001u)
        #define fineMPOut_INTR_FALLING   (uint16)(0x0002u)
        #define fineMPOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fineMPOut_INTR_MASK      (0x01u) 
#endif /* (fineMPOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fineMPOut_PS                     (* (reg8 *) fineMPOut__PS)
/* Data Register */
#define fineMPOut_DR                     (* (reg8 *) fineMPOut__DR)
/* Port Number */
#define fineMPOut_PRT_NUM                (* (reg8 *) fineMPOut__PRT) 
/* Connect to Analog Globals */                                                  
#define fineMPOut_AG                     (* (reg8 *) fineMPOut__AG)                       
/* Analog MUX bux enable */
#define fineMPOut_AMUX                   (* (reg8 *) fineMPOut__AMUX) 
/* Bidirectional Enable */                                                        
#define fineMPOut_BIE                    (* (reg8 *) fineMPOut__BIE)
/* Bit-mask for Aliased Register Access */
#define fineMPOut_BIT_MASK               (* (reg8 *) fineMPOut__BIT_MASK)
/* Bypass Enable */
#define fineMPOut_BYP                    (* (reg8 *) fineMPOut__BYP)
/* Port wide control signals */                                                   
#define fineMPOut_CTL                    (* (reg8 *) fineMPOut__CTL)
/* Drive Modes */
#define fineMPOut_DM0                    (* (reg8 *) fineMPOut__DM0) 
#define fineMPOut_DM1                    (* (reg8 *) fineMPOut__DM1)
#define fineMPOut_DM2                    (* (reg8 *) fineMPOut__DM2) 
/* Input Buffer Disable Override */
#define fineMPOut_INP_DIS                (* (reg8 *) fineMPOut__INP_DIS)
/* LCD Common or Segment Drive */
#define fineMPOut_LCD_COM_SEG            (* (reg8 *) fineMPOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define fineMPOut_LCD_EN                 (* (reg8 *) fineMPOut__LCD_EN)
/* Slew Rate Control */
#define fineMPOut_SLW                    (* (reg8 *) fineMPOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fineMPOut_PRTDSI__CAPS_SEL       (* (reg8 *) fineMPOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fineMPOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fineMPOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fineMPOut_PRTDSI__OE_SEL0        (* (reg8 *) fineMPOut__PRTDSI__OE_SEL0) 
#define fineMPOut_PRTDSI__OE_SEL1        (* (reg8 *) fineMPOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fineMPOut_PRTDSI__OUT_SEL0       (* (reg8 *) fineMPOut__PRTDSI__OUT_SEL0) 
#define fineMPOut_PRTDSI__OUT_SEL1       (* (reg8 *) fineMPOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fineMPOut_PRTDSI__SYNC_OUT       (* (reg8 *) fineMPOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fineMPOut__SIO_CFG)
    #define fineMPOut_SIO_HYST_EN        (* (reg8 *) fineMPOut__SIO_HYST_EN)
    #define fineMPOut_SIO_REG_HIFREQ     (* (reg8 *) fineMPOut__SIO_REG_HIFREQ)
    #define fineMPOut_SIO_CFG            (* (reg8 *) fineMPOut__SIO_CFG)
    #define fineMPOut_SIO_DIFF           (* (reg8 *) fineMPOut__SIO_DIFF)
#endif /* (fineMPOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(fineMPOut__INTSTAT)
    #define fineMPOut_INTSTAT            (* (reg8 *) fineMPOut__INTSTAT)
    #define fineMPOut_SNAP               (* (reg8 *) fineMPOut__SNAP)
    
	#define fineMPOut_0_INTTYPE_REG 		(* (reg8 *) fineMPOut__0__INTTYPE)
#endif /* (fineMPOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fineMPOut_H */


/* [] END OF FILE */
