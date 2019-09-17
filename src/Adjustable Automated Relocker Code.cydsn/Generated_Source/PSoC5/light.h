/*******************************************************************************
* File Name: light.h  
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

#if !defined(CY_PINS_light_H) /* Pins light_H */
#define CY_PINS_light_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "light_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 light__PORT == 15 && ((light__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    light_Write(uint8 value);
void    light_SetDriveMode(uint8 mode);
uint8   light_ReadDataReg(void);
uint8   light_Read(void);
void    light_SetInterruptMode(uint16 position, uint16 mode);
uint8   light_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the light_SetDriveMode() function.
     *  @{
     */
        #define light_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define light_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define light_DM_RES_UP          PIN_DM_RES_UP
        #define light_DM_RES_DWN         PIN_DM_RES_DWN
        #define light_DM_OD_LO           PIN_DM_OD_LO
        #define light_DM_OD_HI           PIN_DM_OD_HI
        #define light_DM_STRONG          PIN_DM_STRONG
        #define light_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define light_MASK               light__MASK
#define light_SHIFT              light__SHIFT
#define light_WIDTH              1u

/* Interrupt constants */
#if defined(light__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in light_SetInterruptMode() function.
     *  @{
     */
        #define light_INTR_NONE      (uint16)(0x0000u)
        #define light_INTR_RISING    (uint16)(0x0001u)
        #define light_INTR_FALLING   (uint16)(0x0002u)
        #define light_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define light_INTR_MASK      (0x01u) 
#endif /* (light__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define light_PS                     (* (reg8 *) light__PS)
/* Data Register */
#define light_DR                     (* (reg8 *) light__DR)
/* Port Number */
#define light_PRT_NUM                (* (reg8 *) light__PRT) 
/* Connect to Analog Globals */                                                  
#define light_AG                     (* (reg8 *) light__AG)                       
/* Analog MUX bux enable */
#define light_AMUX                   (* (reg8 *) light__AMUX) 
/* Bidirectional Enable */                                                        
#define light_BIE                    (* (reg8 *) light__BIE)
/* Bit-mask for Aliased Register Access */
#define light_BIT_MASK               (* (reg8 *) light__BIT_MASK)
/* Bypass Enable */
#define light_BYP                    (* (reg8 *) light__BYP)
/* Port wide control signals */                                                   
#define light_CTL                    (* (reg8 *) light__CTL)
/* Drive Modes */
#define light_DM0                    (* (reg8 *) light__DM0) 
#define light_DM1                    (* (reg8 *) light__DM1)
#define light_DM2                    (* (reg8 *) light__DM2) 
/* Input Buffer Disable Override */
#define light_INP_DIS                (* (reg8 *) light__INP_DIS)
/* LCD Common or Segment Drive */
#define light_LCD_COM_SEG            (* (reg8 *) light__LCD_COM_SEG)
/* Enable Segment LCD */
#define light_LCD_EN                 (* (reg8 *) light__LCD_EN)
/* Slew Rate Control */
#define light_SLW                    (* (reg8 *) light__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define light_PRTDSI__CAPS_SEL       (* (reg8 *) light__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define light_PRTDSI__DBL_SYNC_IN    (* (reg8 *) light__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define light_PRTDSI__OE_SEL0        (* (reg8 *) light__PRTDSI__OE_SEL0) 
#define light_PRTDSI__OE_SEL1        (* (reg8 *) light__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define light_PRTDSI__OUT_SEL0       (* (reg8 *) light__PRTDSI__OUT_SEL0) 
#define light_PRTDSI__OUT_SEL1       (* (reg8 *) light__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define light_PRTDSI__SYNC_OUT       (* (reg8 *) light__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(light__SIO_CFG)
    #define light_SIO_HYST_EN        (* (reg8 *) light__SIO_HYST_EN)
    #define light_SIO_REG_HIFREQ     (* (reg8 *) light__SIO_REG_HIFREQ)
    #define light_SIO_CFG            (* (reg8 *) light__SIO_CFG)
    #define light_SIO_DIFF           (* (reg8 *) light__SIO_DIFF)
#endif /* (light__SIO_CFG) */

/* Interrupt Registers */
#if defined(light__INTSTAT)
    #define light_INTSTAT            (* (reg8 *) light__INTSTAT)
    #define light_SNAP               (* (reg8 *) light__SNAP)
    
	#define light_0_INTTYPE_REG 		(* (reg8 *) light__0__INTTYPE)
#endif /* (light__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_light_H */


/* [] END OF FILE */
