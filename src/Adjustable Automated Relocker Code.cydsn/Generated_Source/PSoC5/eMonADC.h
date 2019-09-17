/*******************************************************************************
* File Name: eMonADC.h
* Version 3.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Successive approximation ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_ADC_SAR_eMonADC_H) /* CY_ADC_SAR_eMonADC_H */
#define CY_ADC_SAR_eMonADC_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component ADC_SAR_v3_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*      Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} eMonADC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void eMonADC_Start(void);
void eMonADC_Stop(void);
void eMonADC_SetPower(uint8 power);
void eMonADC_SetResolution(uint8 resolution);

uint8 eMonADC_IsEndConversion(uint8 retMode);
int8 eMonADC_GetResult8(void);
int16 eMonADC_GetResult16(void);

void eMonADC_SetOffset(int16 offset);
void eMonADC_SetScaledGain(int32 adcGain);
int16 eMonADC_CountsTo_mVolts(int16 adcCounts);
int32 eMonADC_CountsTo_uVolts(int16 adcCounts);
float32 eMonADC_CountsTo_Volts(int16 adcCounts);

void eMonADC_Init(void);
void eMonADC_Enable(void);

void eMonADC_SaveConfig(void);
void eMonADC_RestoreConfig(void);
void eMonADC_Sleep(void);
void eMonADC_Wakeup(void);

CY_ISR_PROTO( eMonADC_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void eMonADC_SetGain(int16 adcGain);


/***************************************
* Global variables external identifier
***************************************/

extern uint8 eMonADC_initVar;
extern volatile int16 eMonADC_offset;
extern volatile int16 eMonADC_countsPerVolt; /* Obsolete variable, do not modify in new design */
extern volatile int32 eMonADC_countsPer10Volt;
extern volatile int16 eMonADC_shift;


/**************************************
*           API Constants
**************************************/

/* Resolution setting constants  */
#define eMonADC__BITS_12 12
#define eMonADC__BITS_10 10
#define eMonADC__BITS_8 8


/*   Constants for IsEndConversion() "retMode" parameter  */
#define eMonADC_RETURN_STATUS              (0x01u)
#define eMonADC_WAIT_FOR_RESULT            (0x00u)

/* Constants for SetPower(power), "power" paramter */
#define eMonADC__HIGHPOWER 0
#define eMonADC__MEDPOWER 1
#define eMonADC__LOWPOWER 2
#define eMonADC__MINPOWER 3

#define eMonADC_SAR_API_POWER_MASK         (0x03u)

/* Constants for Sleep mode states */
#define eMonADC_STARTED                    (0x02u)
#define eMonADC_ENABLED                    (0x01u)
#define eMonADC_DISABLED                   (0x00u)

#define eMonADC_MAX_FREQUENCY              (18000000)       /* 18Mhz */

#define eMonADC_10V_COUNTS                 (10.0F)
#define eMonADC_10MV_COUNTS                (10000)
#define eMonADC_10UV_COUNTS                (10000000L)



/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Reference constants */
#define eMonADC__INT_REF_NOT_BYPASSED 0
#define eMonADC__INT_REF_BYPASS 1
#define eMonADC__EXT_REF 2

/*  Input Range setting constants */
#define eMonADC__VSS_TO_VREF 0
#define eMonADC__VSSA_TO_VDDA 1
#define eMonADC__VSSA_TO_VDAC 2
#define eMonADC__VNEG_VREF_DIFF 3
#define eMonADC__VNEG_VDDA_DIFF 4
#define eMonADC__VNEG_VDDA_2_DIFF 5
#define eMonADC__VNEG_VDAC_DIFF 6

/*  Sample Mode setting constants */
#define eMonADC__FREERUNNING 0
#define eMonADC__TRIGGERED 1

/*  Extended Sample Mode setting constants */
#define eMonADC__FREE_RUNNING 0
#define eMonADC__SOFTWARE_TRIGGER 1
#define eMonADC__HARDWARE_TRIGGER 2

/*  Clock Source setting constants */
#define eMonADC__INTERNAL 1
#define eMonADC__EXTERNAL 0



/**************************************
*    Initial Parameter Constants
**************************************/

/* Default config values from user parameters */
#define eMonADC_DEFAULT_RESOLUTION     (12u)   /* ADC resolution selected with parameters.*/
#define eMonADC_DEFAULT_CONV_MODE      (0u)        /* Default conversion method */
#define eMonADC_DEFAULT_INTERNAL_CLK   (1u)             /* Default clock selection */
#define eMonADC_DEFAULT_REFERENCE      (0u)         /* Default reference */
#define eMonADC_DEFAULT_RANGE          (0u)       /* ADC Input Range selection */
#define eMonADC_CLOCK_FREQUENCY        (1600000u)   /* Clock frequency */
#define eMonADC_NOMINAL_CLOCK_FREQ     (1600000)  /* Nominal Clock Frequency */
#define eMonADC_HIGH_POWER_PULSE       (1u)        /* Not zero when clock pulse > 50 ns */
#define eMonADC_IRQ_REMOVE             (0u)                /* Removes internal interrupt */

/* Use VDDA voltage define directly from cyfitter.h when VDDA reference has been used */
#define eMonADC_DEFAULT_REF_VOLTAGE \
                                   (((eMonADC_DEFAULT_REFERENCE != (uint8)eMonADC__EXT_REF) && \
                                    ((eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VSSA_TO_VDDA) || \
                                     (eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA / 2) : \
                                   (((eMonADC_DEFAULT_REFERENCE != (uint8)eMonADC__EXT_REF) && \
                                     (eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA : (1.024)))      /* ADC reference voltage. */
#define eMonADC_DEFAULT_REF_VOLTAGE_MV \
                                   (((eMonADC_DEFAULT_REFERENCE != (uint8)eMonADC__EXT_REF) && \
                                    ((eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VSSA_TO_VDDA) || \
                                     (eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA_MV / 2) : \
                                  (((eMonADC_DEFAULT_REFERENCE != (uint8)eMonADC__EXT_REF) && \
                                    (eMonADC_DEFAULT_RANGE == (uint8)eMonADC__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA_MV : (1024)))   /* ADC reference voltage in mV */
/* The power is set to normal power, 1/2, 1/4 power depend on the clock setting. */
#define eMonADC_DEFAULT_POWER \
       ((eMonADC_NOMINAL_CLOCK_FREQ > (eMonADC_MAX_FREQUENCY / 4)) ? eMonADC__HIGHPOWER : \
       ((eMonADC_NOMINAL_CLOCK_FREQ > (eMonADC_MAX_FREQUENCY / 8)) ? eMonADC__MEDPOWER : \
                                                                                       eMonADC__MINPOWER))
/* Constant for a global usage */
/* Number of additional clocks for sampling data*/
#define eMonADC_SAMPLE_PRECHARGE       (4u)


/***************************************
*    Optional Function Prototypes
***************************************/

#if(eMonADC_DEFAULT_CONV_MODE != eMonADC__HARDWARE_TRIGGER)
    void eMonADC_StartConvert(void);
    void eMonADC_StopConvert(void);
#endif /* End eMonADC_DEFAULT_CONV_MODE != eMonADC__HARDWARE_TRIGGER */


/***************************************
*              Registers
***************************************/

#define eMonADC_SAR_TR0_REG                (* (reg8 *) eMonADC_ADC_SAR__TR0 )
#define eMonADC_SAR_TR0_PTR                (  (reg8 *) eMonADC_ADC_SAR__TR0 )
#define eMonADC_SAR_CSR0_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR0 )
#define eMonADC_SAR_CSR0_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR0 )
#define eMonADC_SAR_CSR1_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR1 )
#define eMonADC_SAR_CSR1_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR1 )
#define eMonADC_SAR_CSR2_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR2 )
#define eMonADC_SAR_CSR2_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR2 )
#define eMonADC_SAR_CSR3_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR3 )
#define eMonADC_SAR_CSR3_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR3 )
#define eMonADC_SAR_CSR4_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR4 )
#define eMonADC_SAR_CSR4_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR4 )
#define eMonADC_SAR_CSR5_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR5 )
#define eMonADC_SAR_CSR5_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR5 )
#define eMonADC_SAR_CSR6_REG               (* (reg8 *) eMonADC_ADC_SAR__CSR6 )
#define eMonADC_SAR_CSR6_PTR               (  (reg8 *) eMonADC_ADC_SAR__CSR6 )
#define eMonADC_SAR_SW0_REG                (* (reg8 *) eMonADC_ADC_SAR__SW0 )
#define eMonADC_SAR_SW0_PTR                (  (reg8 *) eMonADC_ADC_SAR__SW0 )
#define eMonADC_SAR_SW2_REG                (* (reg8 *) eMonADC_ADC_SAR__SW2 )
#define eMonADC_SAR_SW2_PTR                (  (reg8 *) eMonADC_ADC_SAR__SW2 )
#define eMonADC_SAR_SW3_REG                (* (reg8 *) eMonADC_ADC_SAR__SW3 )
#define eMonADC_SAR_SW3_PTR                (  (reg8 *) eMonADC_ADC_SAR__SW3 )
#define eMonADC_SAR_SW4_REG                (* (reg8 *) eMonADC_ADC_SAR__SW4 )
#define eMonADC_SAR_SW4_PTR                (  (reg8 *) eMonADC_ADC_SAR__SW4 )
#define eMonADC_SAR_SW6_REG                (* (reg8 *) eMonADC_ADC_SAR__SW6 )
#define eMonADC_SAR_SW6_PTR                (  (reg8 *) eMonADC_ADC_SAR__SW6 )
#define eMonADC_SAR_CLK_REG                (* (reg8 *) eMonADC_ADC_SAR__CLK )
#define eMonADC_SAR_CLK_PTR                (  (reg8 *) eMonADC_ADC_SAR__CLK )
#define eMonADC_SAR_WRK0_REG               (* (reg8 *) eMonADC_ADC_SAR__WRK0 )
#define eMonADC_SAR_WRK0_PTR               (  (reg8 *) eMonADC_ADC_SAR__WRK0 )
#define eMonADC_SAR_WRK1_REG               (* (reg8 *) eMonADC_ADC_SAR__WRK1 )
#define eMonADC_SAR_WRK1_PTR               (  (reg8 *) eMonADC_ADC_SAR__WRK1 )
#define eMonADC_SAR_WRK_PTR                (  (reg16 *) eMonADC_ADC_SAR__WRK0 )
#define eMonADC_PWRMGR_SAR_REG             (* (reg8 *) eMonADC_ADC_SAR__PM_ACT_CFG )
#define eMonADC_PWRMGR_SAR_PTR             (  (reg8 *) eMonADC_ADC_SAR__PM_ACT_CFG )
#define eMonADC_STBY_PWRMGR_SAR_REG        (* (reg8 *) eMonADC_ADC_SAR__PM_STBY_CFG )
#define eMonADC_STBY_PWRMGR_SAR_PTR        (  (reg8 *) eMonADC_ADC_SAR__PM_STBY_CFG )

/* renamed registers for backward compatible */
#define eMonADC_SAR_WRK0                   eMonADC_SAR_WRK0_REG
#define eMonADC_SAR_WRK1                   eMonADC_SAR_WRK1_REG

/* This is only valid if there is an internal clock */
#if(eMonADC_DEFAULT_INTERNAL_CLK)
    /* Clock Power manager Reg */
    #define eMonADC_PWRMGR_CLK_REG         (* (reg8 *) eMonADC_theACLK__PM_ACT_CFG )
    #define eMonADC_PWRMGR_CLK_PTR         (  (reg8 *) eMonADC_theACLK__PM_ACT_CFG )
    #define eMonADC_STBY_PWRMGR_CLK_REG    (* (reg8 *) eMonADC_theACLK__PM_STBY_CFG )
    #define eMonADC_STBY_PWRMGR_CLK_PTR    (  (reg8 *) eMonADC_theACLK__PM_STBY_CFG )
#endif /*End eMonADC_DEFAULT_INTERNAL_CLK */


/**************************************
*       Register Constants
**************************************/
/* PM_ACT_CFG (Active Power Mode CFG Register) Power enable mask */
#define eMonADC_ACT_PWR_SAR_EN             (uint8)(eMonADC_ADC_SAR__PM_ACT_MSK)

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register) Power enable mask */
#define eMonADC_STBY_PWR_SAR_EN            (uint8)(eMonADC_ADC_SAR__PM_STBY_MSK)

/* This is only valid if there is an internal clock */
#if(eMonADC_DEFAULT_INTERNAL_CLK)
    /* Power enable mask */
    #define eMonADC_ACT_PWR_CLK_EN         (uint8)(eMonADC_theACLK__PM_ACT_MSK)
    /* Standby power enable mask */
    #define eMonADC_STBY_PWR_CLK_EN        (uint8)(eMonADC_theACLK__PM_STBY_MSK)
#endif /*End eMonADC_DEFAULT_INTERNAL_CLK */

#if(eMonADC_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define eMonADC_INTC_PRIOR_NUMBER          (uint8)(eMonADC_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define eMonADC_INTC_NUMBER                (uint8)(eMonADC_IRQ__INTC_NUMBER)

#endif   /* End eMonADC_IRQ_REMOVE */


/******************************************/
/* SAR.TR0 Trim Register 0 definitions    */
/******************************************/

/* Bit Field  SAR_CAP_TRIM_ENUM */
#define eMonADC_SAR_CAP_TRIM_MASK          (0x07u)
#define eMonADC_SAR_CAP_TRIM_0             (0x00u)    /*decrease attenuation capacitor by 0*/
#define eMonADC_SAR_CAP_TRIM_1             (0x01u)    /*decrease by 0.5 LSB*/
#define eMonADC_SAR_CAP_TRIM_2             (0x02u)    /*decrease by 2*0.5 LSB = 1 LSB*/
#define eMonADC_SAR_CAP_TRIM_3             (0x03u)    /*decrease by 3*0.5 LSB = 1.5 LSB*/
#define eMonADC_SAR_CAP_TRIM_4             (0x04u)    /*decrease by 4*0.5 LSB = 2 LSB*/
#define eMonADC_SAR_CAP_TRIM_5             (0x05u)    /*decrease by 5*0.5 LSB = 2.5 LSB*/
#define eMonADC_SAR_CAP_TRIM_6             (0x06u)    /*decrease by 6*0.5 LSB = 3 LSB*/
#define eMonADC_SAR_CAP_TRIM_7             (0x07u)    /*decrease by 7*0.5 LSB = 3.5 LSB*/

#define eMonADC_SAR_TRIMUNIT               (0x08u)    /*Increase by 6fF*/

/*******************************************************/
/* SAR.CSR0 Satatus and Control Register 0 definitions */
/*******************************************************/

/* Bit Field  SAR_ICONT_LV_ENUM */
#define eMonADC_SAR_POWER_MASK             (0xC0u)
#define eMonADC_SAR_POWER_SHIFT            (0x06u)
#define eMonADC_ICONT_LV_0                 (0x00u)
#define eMonADC_ICONT_LV_1                 (0x40u)
#define eMonADC_ICONT_LV_2                 (0x80u)
#define eMonADC_ICONT_LV_3                 (0xC0u)
#define eMonADC_ICONT_FULL_CURRENT         (0x00u)

/* Bit Field SAR_RESET_SOFT_ENUM */
#define eMonADC_SAR_RESET_SOFT_NOTACTIVE   (0x00u)
#define eMonADC_SAR_RESET_SOFT_ACTIVE      (0x20u)

/* Bit Field  SAR_COHERENCY_EN_ENUM */
#define eMonADC_SAR_COHERENCY_EN_NOLOCK    (0x00u)
#define eMonADC_SAR_COHERENCY_EN_LOCK      (0x10u)

/* Bit Field  SAR_HIZ_ENUM */
#define eMonADC_SAR_HIZ_RETAIN             (0x00u)
#define eMonADC_SAR_HIZ_CLEAR              (0x08u)

/* Bit Field SAR_MX_SOF_ENUM */
#define eMonADC_SAR_MX_SOF_BIT             (0x00u)
#define eMonADC_SAR_MX_SOF_UDB             (0x04u)

/* Bit Field SAR_SOF_MODE_ENUM */
#define eMonADC_SAR_SOF_MODE_LEVEL         (0x00u)
#define eMonADC_SAR_SOF_MODE_EDGE          (0x02u)

/* Bit Field SAR_SOF_BIT_ENUM */
#define eMonADC_SAR_SOF_STOP_CONV          (0x00u)            /* Disable conversion */
#define eMonADC_SAR_SOF_START_CONV         (0x01u)            /* Enable conversion */

/*******************************************************/
/* SAR.CSR1 Satatus and Control Register 1 definitions */
/*******************************************************/

/* Bit Field  SAR_MUXREF_ENUM */
#define eMonADC_SAR_MUXREF_MASK            (0xE0u)
#define eMonADC_SAR_MUXREF_NONE            (0x00u)
#define eMonADC_SAR_MUXREF_VDDA_2          (0x40u)
#define eMonADC_SAR_MUXREF_DAC             (0x60u)
#define eMonADC_SAR_MUXREF_1_024V          (0x80u)
#define eMonADC_SAR_MUXREF_1_20V           (0xA0u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define eMonADC_SAR_SWVP_SRC_REG           (0x00u)
#define eMonADC_SAR_SWVP_SRC_UDB           (0x10u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define eMonADC_SAR_SWVN_SRC_REG           (0x00u)
#define eMonADC_SAR_SWVN_SRC_UDB           (0x08u)

/* Bit Field  SAR_IRQ_MODE_ENUM */
#define eMonADC_SAR_IRQ_MODE_LEVEL         (0x00u)
#define eMonADC_SAR_IRQ_MODE_EDGE          (0x04u)

/* Bit Field  SAR_IRQ_MASK_ENUM */
#define eMonADC_SAR_IRQ_MASK_DIS           (0x00u)
#define eMonADC_SAR_IRQ_MASK_EN            (0x02u)

/* Bit Field  SAR_EOF_ENUM */
#define eMonADC_SAR_EOF_0                  (0x00u)
#define eMonADC_SAR_EOF_1                  (0x01u)

/*******************************************************/
/* SAR.CSR2 Satatus and Control Register 2 definitions */
/*******************************************************/

/* Bit Field  SAR_RESOLUTION_ENUM */
#define eMonADC_SAR_RESOLUTION_MASK        (0xC0u)
#define eMonADC_SAR_RESOLUTION_SHIFT       (0x06u)
#define eMonADC_SAR_RESOLUTION_12BIT       (0xC0u)
#define eMonADC_SAR_RESOLUTION_10BIT       (0x80u)
#define eMonADC_SAR_RESOLUTION_8BIT        (0x40u)

/* Bit Field SAR_SAMPLE_WIDTH_ENUM */
#define eMonADC_SAR_SAMPLE_WIDTH_MASK      (0x3Fu)
#define eMonADC_SAR_SAMPLE_WIDTH_MIN       (0x00u)   /* minimum sample time: +1 clock cycle */
#define eMonADC_SAR_SAMPLE_WIDTH           (eMonADC_SAMPLE_PRECHARGE - 0x02u)
#define eMonADC_SAR_SAMPLE_WIDTH_MAX       (0x07u)   /* maximum sample time: +8 clock cycles */

/*******************************************************/
/* SAR.CSR3 Satatus and Control Register 3 definitions */
/*******************************************************/

/* Bit Field  SAR_EN_CP_ENUM */
#define eMonADC_SAR_EN_CP_DIS              (0x00u)
#define eMonADC_SAR_EN_CP_EN               (0x80u)

/* Bit Field  SAR_EN_RESVDA_ENUM */
#define eMonADC_SAR_EN_RESVDA_DIS          (0x00u)
#define eMonADC_SAR_EN_RESVDA_EN           (0x40u)

/* Bit Field  SAR_PWR_CTRL_VCM_ENUM */
#define eMonADC_SAR_PWR_CTRL_VCM_MASK      (0x30u)
#define eMonADC_SAR_PWR_CTRL_VCM_0         (0x00u)
#define eMonADC_SAR_PWR_CTRL_VCM_1         (0x10u)
#define eMonADC_SAR_PWR_CTRL_VCM_2         (0x20u)
#define eMonADC_SAR_PWR_CTRL_VCM_3         (0x30u)

/* Bit Field  SAR_PWR_CTRL_VREF_ENUM */
#define eMonADC_SAR_PWR_CTRL_VREF_MASK     (0x0Cu)
#define eMonADC_SAR_PWR_CTRL_VREF_0        (0x00u)
#define eMonADC_SAR_PWR_CTRL_VREF_DIV_BY2  (0x04u)
#define eMonADC_SAR_PWR_CTRL_VREF_DIV_BY3  (0x08u)
#define eMonADC_SAR_PWR_CTRL_VREF_DIV_BY4  (0x0Cu)

/* Bit Field  SAR_EN_BUF_VCM_ENUM */
#define eMonADC_SAR_EN_BUF_VCM_DIS         (0x00u)
#define eMonADC_SAR_EN_BUF_VCM_EN          (0x02u)

/* Bit Field  SAR_EN_BUF_VREF_ENUM */
#define eMonADC_SAR_EN_BUF_VREF_DIS        (0x00u)
#define eMonADC_SAR_EN_BUF_VREF_EN         (0x01u)

/*******************************************************/
/* SAR.CSR4 Satatus and Control Register 4 definitions */
/*******************************************************/

/* Bit Field  SAR_DFT_INC_ENUM */
#define eMonADC_SAR_DFT_INC_MASK           (0x0Fu)
#define eMonADC_SAR_DFT_INC_DIS            (0x00u)
#define eMonADC_SAR_DFT_INC_EN             (0x0Fu)

/* Bit Field  SAR_DFT_INC_ENUM */
#define eMonADC_SAR_DFT_OUTC_MASK          (0x70u)
#define eMonADC_SAR_DFT_OUTC_DIS           (0x00u)
#define eMonADC_SAR_DFT_OUTC_EN            (0x70u)

/*******************************************************/
/* SAR.CSR5 Satatus and Control Register 5 definitions */
/*******************************************************/

/* Bit Field  SAR_OVERRUN_DET_EN_ENUM */
#define eMonADC_SAR_OVERRUN_DET_EN_EN      (0x80u)

/* Bit Field  SAR_DLY_INC_ENUM */
#define eMonADC_SAR_DLY_INC                (0x40u)

/* Bit Field  SAR_DCEN_ENUM */
#define eMonADC_SAR_DCEN                   (0x20u)

/* Bit Field  SAR_EN_CSEL_DFT_ENUM */
#define eMonADC_SAR_EN_CSEL_DFT_DISABLED   (0x00u)
#define eMonADC_SAR_EN_CSEL_DFT_ENABLED    (0x10u)

/* Bit Field  SAR_SEL_CSEL_DFT_ENUM */
#define eMonADC_SAR_SEL_CSEL_DFT_MASK      (0x0Fu)
#define eMonADC_SAR_SEL_CSEL_DFT_MIN       (0x00u)
#define eMonADC_SAR_SEL_CSEL_DFT_MAX       (0x0Fu)
#define eMonADC_SAR_SEL_CSEL_DFT_CHAR      (0x03u)

/*******************************************************/
/* SAR.CSR6 Satatus and Control Register 6 definitions */
/*******************************************************/
#define eMonADC_INT_VREF                   (0x18u)
#define eMonADC_INT_BYPASS_EXT_VREF        (0x04u)
#define eMonADC_VDDA_VREF                  (0x80u)

/*******************************************************/
/* SAR.CSR7 Satatus and Control Register 7 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_ENUM */
#define eMonADC_SAR_REF_S_MSB_MASK         (0x3Fu)
#define eMonADC_SAR_REF_S_MSB_DIS          (0x00u)
#define eMonADC_SAR_REF_S8_MSB_DIS         (0x01u)
#define eMonADC_SAR_REF_S9_MSB_EN          (0x02u)
#define eMonADC_SAR_REF_S10_MSB_EN         (0x04u)
#define eMonADC_SAR_REF_S11_MSB_EN         (0x08u)
#define eMonADC_SAR_REF_S12_MSB_EN         (0x10u)
#define eMonADC_SAR_REF_S13_MSB_EN         (0x20u)

/*******************************************************/
/* SAR.CLK SAR Clock Selection Register definitions    */
/*******************************************************/

/* Bit Field  MX_PUMPCLK_ENUM */
#define eMonADC_SAR_MX_PUMPCLK_MASK        (0xE0u)
#define eMonADC_SAR_MX_PUMPCLK_0           (0x00u)
#define eMonADC_SAR_MX_PUMPCLK_1           (0x20u)
#define eMonADC_SAR_MX_PUMPCLK_2           (0x40u)
#define eMonADC_SAR_MX_PUMPCLK_3           (0x60u)
#define eMonADC_SAR_MX_PUMPCLK_4           (0x80u)

/* Bit Field  BYPASS_SYNC_ENUM */
#define eMonADC_SAR_BYPASS_SYNC_0          (0x00u)
#define eMonADC_SAR_BYPASS_SYNC_1          (0x10u)

/* Bit Field  MX_CLK_EN_ENUM */
#define eMonADC_SAR_MX_CLK_EN              (0x08u)

/* Bit Field  MX_CLK_ENUM  */
#define eMonADC_SAR_MX_CLK_MASK            (0x07u)
#define eMonADC_SAR_MX_CLK_0               (0x00u)
#define eMonADC_SAR_MX_CLK_1               (0x01u)
#define eMonADC_SAR_MX_CLK_2               (0x02u)
#define eMonADC_SAR_MX_CLK_3               (0x03u)
#define eMonADC_SAR_MX_CLK_4               (0x04u)

/*********************************************************/
/* ANAIF.WRK.SARS.SOF SAR Global Start-of-frame register */
/*********************************************************/

/* Bit Field  SAR_SOF_BIT_ENUM */
#define eMonADC_SAR_SOFR_BIT_MASK          (0x03u)
#define eMonADC_SAR_SOFR_BIT_0             (0x00u)
#define eMonADC_SAR_SOFR_BIT_1             (0x01u)

/***********************************************/
/* SAR.SW3 SAR Analog Routing Register 3       */
/***********************************************/
#define eMonADC_SAR_VP_VSSA                (0x04u)
#define eMonADC_SAR_VN_AMX                 (0x10u)
#define eMonADC_SAR_VN_VREF                (0x20u)
#define eMonADC_SAR_VN_VSSA                (0x40u)
#define eMonADC_SAR_VN_MASK                (0x60u)

/***********************************************/
/* SAR.WRKx SAR Working Register               */
/***********************************************/
#define eMonADC_SAR_WRK_MAX                (0xFFFu)
#define eMonADC_SAR_DIFF_SHIFT             (0x800u)

/* Absolute maximum counts equivalent reference voltage */
#define eMonADC_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define eMonADC_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define eMonADC_SAR_WRK_MAX_8BIT           (0x00000100Lu)


#endif /* End CY_ADC_SAR_eMonADC_H */


/* [] END OF FILE */
