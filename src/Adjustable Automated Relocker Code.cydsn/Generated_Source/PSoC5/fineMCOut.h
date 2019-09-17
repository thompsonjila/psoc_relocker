/*******************************************************************************
* File Name: fineMCOut.h  
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

#if !defined(CY_PINS_fineMCOut_H) /* Pins fineMCOut_H */
#define CY_PINS_fineMCOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "fineMCOut_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 fineMCOut__PORT == 15 && ((fineMCOut__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    fineMCOut_Write(uint8 value);
void    fineMCOut_SetDriveMode(uint8 mode);
uint8   fineMCOut_ReadDataReg(void);
uint8   fineMCOut_Read(void);
void    fineMCOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   fineMCOut_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the fineMCOut_SetDriveMode() function.
     *  @{
     */
        #define fineMCOut_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define fineMCOut_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define fineMCOut_DM_RES_UP          PIN_DM_RES_UP
        #define fineMCOut_DM_RES_DWN         PIN_DM_RES_DWN
        #define fineMCOut_DM_OD_LO           PIN_DM_OD_LO
        #define fineMCOut_DM_OD_HI           PIN_DM_OD_HI
        #define fineMCOut_DM_STRONG          PIN_DM_STRONG
        #define fineMCOut_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define fineMCOut_MASK               fineMCOut__MASK
#define fineMCOut_SHIFT              fineMCOut__SHIFT
#define fineMCOut_WIDTH              1u

/* Interrupt constants */
#if defined(fineMCOut__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in fineMCOut_SetInterruptMode() function.
     *  @{
     */
        #define fineMCOut_INTR_NONE      (uint16)(0x0000u)
        #define fineMCOut_INTR_RISING    (uint16)(0x0001u)
        #define fineMCOut_INTR_FALLING   (uint16)(0x0002u)
        #define fineMCOut_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define fineMCOut_INTR_MASK      (0x01u) 
#endif /* (fineMCOut__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define fineMCOut_PS                     (* (reg8 *) fineMCOut__PS)
/* Data Register */
#define fineMCOut_DR                     (* (reg8 *) fineMCOut__DR)
/* Port Number */
#define fineMCOut_PRT_NUM                (* (reg8 *) fineMCOut__PRT) 
/* Connect to Analog Globals */                                                  
#define fineMCOut_AG                     (* (reg8 *) fineMCOut__AG)                       
/* Analog MUX bux enable */
#define fineMCOut_AMUX                   (* (reg8 *) fineMCOut__AMUX) 
/* Bidirectional Enable */                                                        
#define fineMCOut_BIE                    (* (reg8 *) fineMCOut__BIE)
/* Bit-mask for Aliased Register Access */
#define fineMCOut_BIT_MASK               (* (reg8 *) fineMCOut__BIT_MASK)
/* Bypass Enable */
#define fineMCOut_BYP                    (* (reg8 *) fineMCOut__BYP)
/* Port wide control signals */                                                   
#define fineMCOut_CTL                    (* (reg8 *) fineMCOut__CTL)
/* Drive Modes */
#define fineMCOut_DM0                    (* (reg8 *) fineMCOut__DM0) 
#define fineMCOut_DM1                    (* (reg8 *) fineMCOut__DM1)
#define fineMCOut_DM2                    (* (reg8 *) fineMCOut__DM2) 
/* Input Buffer Disable Override */
#define fineMCOut_INP_DIS                (* (reg8 *) fineMCOut__INP_DIS)
/* LCD Common or Segment Drive */
#define fineMCOut_LCD_COM_SEG            (* (reg8 *) fineMCOut__LCD_COM_SEG)
/* Enable Segment LCD */
#define fineMCOut_LCD_EN                 (* (reg8 *) fineMCOut__LCD_EN)
/* Slew Rate Control */
#define fineMCOut_SLW                    (* (reg8 *) fineMCOut__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define fineMCOut_PRTDSI__CAPS_SEL       (* (reg8 *) fineMCOut__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define fineMCOut_PRTDSI__DBL_SYNC_IN    (* (reg8 *) fineMCOut__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define fineMCOut_PRTDSI__OE_SEL0        (* (reg8 *) fineMCOut__PRTDSI__OE_SEL0) 
#define fineMCOut_PRTDSI__OE_SEL1        (* (reg8 *) fineMCOut__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define fineMCOut_PRTDSI__OUT_SEL0       (* (reg8 *) fineMCOut__PRTDSI__OUT_SEL0) 
#define fineMCOut_PRTDSI__OUT_SEL1       (* (reg8 *) fineMCOut__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define fineMCOut_PRTDSI__SYNC_OUT       (* (reg8 *) fineMCOut__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(fineMCOut__SIO_CFG)
    #define fineMCOut_SIO_HYST_EN        (* (reg8 *) fineMCOut__SIO_HYST_EN)
    #define fineMCOut_SIO_REG_HIFREQ     (* (reg8 *) fineMCOut__SIO_REG_HIFREQ)
    #define fineMCOut_SIO_CFG            (* (reg8 *) fineMCOut__SIO_CFG)
    #define fineMCOut_SIO_DIFF           (* (reg8 *) fineMCOut__SIO_DIFF)
#endif /* (fineMCOut__SIO_CFG) */

/* Interrupt Registers */
#if defined(fineMCOut__INTSTAT)
    #define fineMCOut_INTSTAT            (* (reg8 *) fineMCOut__INTSTAT)
    #define fineMCOut_SNAP               (* (reg8 *) fineMCOut__SNAP)
    
	#define fineMCOut_0_INTTYPE_REG 		(* (reg8 *) fineMCOut__0__INTTYPE)
#endif /* (fineMCOut__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_fineMCOut_H */


/* [] END OF FILE */
