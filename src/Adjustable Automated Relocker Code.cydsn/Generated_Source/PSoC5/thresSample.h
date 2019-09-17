/*******************************************************************************
* File Name: thresSample.h  
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

#if !defined(CY_PINS_thresSample_H) /* Pins thresSample_H */
#define CY_PINS_thresSample_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "thresSample_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 thresSample__PORT == 15 && ((thresSample__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    thresSample_Write(uint8 value);
void    thresSample_SetDriveMode(uint8 mode);
uint8   thresSample_ReadDataReg(void);
uint8   thresSample_Read(void);
void    thresSample_SetInterruptMode(uint16 position, uint16 mode);
uint8   thresSample_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the thresSample_SetDriveMode() function.
     *  @{
     */
        #define thresSample_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define thresSample_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define thresSample_DM_RES_UP          PIN_DM_RES_UP
        #define thresSample_DM_RES_DWN         PIN_DM_RES_DWN
        #define thresSample_DM_OD_LO           PIN_DM_OD_LO
        #define thresSample_DM_OD_HI           PIN_DM_OD_HI
        #define thresSample_DM_STRONG          PIN_DM_STRONG
        #define thresSample_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define thresSample_MASK               thresSample__MASK
#define thresSample_SHIFT              thresSample__SHIFT
#define thresSample_WIDTH              1u

/* Interrupt constants */
#if defined(thresSample__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in thresSample_SetInterruptMode() function.
     *  @{
     */
        #define thresSample_INTR_NONE      (uint16)(0x0000u)
        #define thresSample_INTR_RISING    (uint16)(0x0001u)
        #define thresSample_INTR_FALLING   (uint16)(0x0002u)
        #define thresSample_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define thresSample_INTR_MASK      (0x01u) 
#endif /* (thresSample__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define thresSample_PS                     (* (reg8 *) thresSample__PS)
/* Data Register */
#define thresSample_DR                     (* (reg8 *) thresSample__DR)
/* Port Number */
#define thresSample_PRT_NUM                (* (reg8 *) thresSample__PRT) 
/* Connect to Analog Globals */                                                  
#define thresSample_AG                     (* (reg8 *) thresSample__AG)                       
/* Analog MUX bux enable */
#define thresSample_AMUX                   (* (reg8 *) thresSample__AMUX) 
/* Bidirectional Enable */                                                        
#define thresSample_BIE                    (* (reg8 *) thresSample__BIE)
/* Bit-mask for Aliased Register Access */
#define thresSample_BIT_MASK               (* (reg8 *) thresSample__BIT_MASK)
/* Bypass Enable */
#define thresSample_BYP                    (* (reg8 *) thresSample__BYP)
/* Port wide control signals */                                                   
#define thresSample_CTL                    (* (reg8 *) thresSample__CTL)
/* Drive Modes */
#define thresSample_DM0                    (* (reg8 *) thresSample__DM0) 
#define thresSample_DM1                    (* (reg8 *) thresSample__DM1)
#define thresSample_DM2                    (* (reg8 *) thresSample__DM2) 
/* Input Buffer Disable Override */
#define thresSample_INP_DIS                (* (reg8 *) thresSample__INP_DIS)
/* LCD Common or Segment Drive */
#define thresSample_LCD_COM_SEG            (* (reg8 *) thresSample__LCD_COM_SEG)
/* Enable Segment LCD */
#define thresSample_LCD_EN                 (* (reg8 *) thresSample__LCD_EN)
/* Slew Rate Control */
#define thresSample_SLW                    (* (reg8 *) thresSample__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define thresSample_PRTDSI__CAPS_SEL       (* (reg8 *) thresSample__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define thresSample_PRTDSI__DBL_SYNC_IN    (* (reg8 *) thresSample__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define thresSample_PRTDSI__OE_SEL0        (* (reg8 *) thresSample__PRTDSI__OE_SEL0) 
#define thresSample_PRTDSI__OE_SEL1        (* (reg8 *) thresSample__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define thresSample_PRTDSI__OUT_SEL0       (* (reg8 *) thresSample__PRTDSI__OUT_SEL0) 
#define thresSample_PRTDSI__OUT_SEL1       (* (reg8 *) thresSample__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define thresSample_PRTDSI__SYNC_OUT       (* (reg8 *) thresSample__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(thresSample__SIO_CFG)
    #define thresSample_SIO_HYST_EN        (* (reg8 *) thresSample__SIO_HYST_EN)
    #define thresSample_SIO_REG_HIFREQ     (* (reg8 *) thresSample__SIO_REG_HIFREQ)
    #define thresSample_SIO_CFG            (* (reg8 *) thresSample__SIO_CFG)
    #define thresSample_SIO_DIFF           (* (reg8 *) thresSample__SIO_DIFF)
#endif /* (thresSample__SIO_CFG) */

/* Interrupt Registers */
#if defined(thresSample__INTSTAT)
    #define thresSample_INTSTAT            (* (reg8 *) thresSample__INTSTAT)
    #define thresSample_SNAP               (* (reg8 *) thresSample__SNAP)
    
	#define thresSample_0_INTTYPE_REG 		(* (reg8 *) thresSample__0__INTTYPE)
#endif /* (thresSample__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_thresSample_H */


/* [] END OF FILE */
