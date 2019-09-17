/*******************************************************************************
* File Name: errMonADC.h
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


#if !defined(CY_ADC_SAR_errMonADC_H) /* CY_ADC_SAR_errMonADC_H */
#define CY_ADC_SAR_errMonADC_H

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
} errMonADC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void errMonADC_Start(void);
void errMonADC_Stop(void);
void errMonADC_SetPower(uint8 power);
void errMonADC_SetResolution(uint8 resolution);

uint8 errMonADC_IsEndConversion(uint8 retMode);
int8 errMonADC_GetResult8(void);
int16 errMonADC_GetResult16(void);

void errMonADC_SetOffset(int16 offset);
void errMonADC_SetScaledGain(int32 adcGain);
int16 errMonADC_CountsTo_mVolts(int16 adcCounts);
int32 errMonADC_CountsTo_uVolts(int16 adcCounts);
float32 errMonADC_CountsTo_Volts(int16 adcCounts);

void errMonADC_Init(void);
void errMonADC_Enable(void);

void errMonADC_SaveConfig(void);
void errMonADC_RestoreConfig(void);
void errMonADC_Sleep(void);
void errMonADC_Wakeup(void);

CY_ISR_PROTO( errMonADC_ISR );

/* Obsolete API for backward compatibility.
*  Should not be used in new designs.
*/
void errMonADC_SetGain(int16 adcGain);


/***************************************
* Global variables external identifier
***************************************/

extern uint8 errMonADC_initVar;
extern volatile int16 errMonADC_offset;
extern volatile int16 errMonADC_countsPerVolt; /* Obsolete variable, do not modify in new design */
extern volatile int32 errMonADC_countsPer10Volt;
extern volatile int16 errMonADC_shift;


/**************************************
*           API Constants
**************************************/

/* Resolution setting constants  */
#define errMonADC__BITS_12 12
#define errMonADC__BITS_10 10
#define errMonADC__BITS_8 8


/*   Constants for IsEndConversion() "retMode" parameter  */
#define errMonADC_RETURN_STATUS              (0x01u)
#define errMonADC_WAIT_FOR_RESULT            (0x00u)

/* Constants for SetPower(power), "power" paramter */
#define errMonADC__HIGHPOWER 0
#define errMonADC__MEDPOWER 1
#define errMonADC__LOWPOWER 2
#define errMonADC__MINPOWER 3

#define errMonADC_SAR_API_POWER_MASK         (0x03u)

/* Constants for Sleep mode states */
#define errMonADC_STARTED                    (0x02u)
#define errMonADC_ENABLED                    (0x01u)
#define errMonADC_DISABLED                   (0x00u)

#define errMonADC_MAX_FREQUENCY              (18000000)       /* 18Mhz */

#define errMonADC_10V_COUNTS                 (10.0F)
#define errMonADC_10MV_COUNTS                (10000)
#define errMonADC_10UV_COUNTS                (10000000L)



/**************************************
*    Enumerated Types and Parameters
**************************************/

/*  Reference constants */
#define errMonADC__INT_REF_NOT_BYPASSED 0
#define errMonADC__INT_REF_BYPASS 1
#define errMonADC__EXT_REF 2

/*  Input Range setting constants */
#define errMonADC__VSS_TO_VREF 0
#define errMonADC__VSSA_TO_VDDA 1
#define errMonADC__VSSA_TO_VDAC 2
#define errMonADC__VNEG_VREF_DIFF 3
#define errMonADC__VNEG_VDDA_DIFF 4
#define errMonADC__VNEG_VDDA_2_DIFF 5
#define errMonADC__VNEG_VDAC_DIFF 6

/*  Sample Mode setting constants */
#define errMonADC__FREERUNNING 0
#define errMonADC__TRIGGERED 1

/*  Extended Sample Mode setting constants */
#define errMonADC__FREE_RUNNING 0
#define errMonADC__SOFTWARE_TRIGGER 1
#define errMonADC__HARDWARE_TRIGGER 2

/*  Clock Source setting constants */
#define errMonADC__INTERNAL 1
#define errMonADC__EXTERNAL 0



/**************************************
*    Initial Parameter Constants
**************************************/

/* Default config values from user parameters */
#define errMonADC_DEFAULT_RESOLUTION     (12u)   /* ADC resolution selected with parameters.*/
#define errMonADC_DEFAULT_CONV_MODE      (0u)        /* Default conversion method */
#define errMonADC_DEFAULT_INTERNAL_CLK   (1u)             /* Default clock selection */
#define errMonADC_DEFAULT_REFERENCE      (0u)         /* Default reference */
#define errMonADC_DEFAULT_RANGE          (0u)       /* ADC Input Range selection */
#define errMonADC_CLOCK_FREQUENCY        (1600000u)   /* Clock frequency */
#define errMonADC_NOMINAL_CLOCK_FREQ     (1600000)  /* Nominal Clock Frequency */
#define errMonADC_HIGH_POWER_PULSE       (1u)        /* Not zero when clock pulse > 50 ns */
#define errMonADC_IRQ_REMOVE             (0u)                /* Removes internal interrupt */

/* Use VDDA voltage define directly from cyfitter.h when VDDA reference has been used */
#define errMonADC_DEFAULT_REF_VOLTAGE \
                                   (((errMonADC_DEFAULT_REFERENCE != (uint8)errMonADC__EXT_REF) && \
                                    ((errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VSSA_TO_VDDA) || \
                                     (errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA / 2) : \
                                   (((errMonADC_DEFAULT_REFERENCE != (uint8)errMonADC__EXT_REF) && \
                                     (errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA : (1.024)))      /* ADC reference voltage. */
#define errMonADC_DEFAULT_REF_VOLTAGE_MV \
                                   (((errMonADC_DEFAULT_REFERENCE != (uint8)errMonADC__EXT_REF) && \
                                    ((errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VSSA_TO_VDDA) || \
                                     (errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VNEG_VDDA_2_DIFF))) ? \
                                     (CYDEV_VDDA_MV / 2) : \
                                  (((errMonADC_DEFAULT_REFERENCE != (uint8)errMonADC__EXT_REF) && \
                                    (errMonADC_DEFAULT_RANGE == (uint8)errMonADC__VNEG_VDDA_2_DIFF)) ? \
                                     CYDEV_VDDA_MV : (1024)))   /* ADC reference voltage in mV */
/* The power is set to normal power, 1/2, 1/4 power depend on the clock setting. */
#define errMonADC_DEFAULT_POWER \
       ((errMonADC_NOMINAL_CLOCK_FREQ > (errMonADC_MAX_FREQUENCY / 4)) ? errMonADC__HIGHPOWER : \
       ((errMonADC_NOMINAL_CLOCK_FREQ > (errMonADC_MAX_FREQUENCY / 8)) ? errMonADC__MEDPOWER : \
                                                                                       errMonADC__MINPOWER))
/* Constant for a global usage */
/* Number of additional clocks for sampling data*/
#define errMonADC_SAMPLE_PRECHARGE       (4u)


/***************************************
*    Optional Function Prototypes
***************************************/

#if(errMonADC_DEFAULT_CONV_MODE != errMonADC__HARDWARE_TRIGGER)
    void errMonADC_StartConvert(void);
    void errMonADC_StopConvert(void);
#endif /* End errMonADC_DEFAULT_CONV_MODE != errMonADC__HARDWARE_TRIGGER */


/***************************************
*              Registers
***************************************/

#define errMonADC_SAR_TR0_REG                (* (reg8 *) errMonADC_ADC_SAR__TR0 )
#define errMonADC_SAR_TR0_PTR                (  (reg8 *) errMonADC_ADC_SAR__TR0 )
#define errMonADC_SAR_CSR0_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR0 )
#define errMonADC_SAR_CSR0_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR0 )
#define errMonADC_SAR_CSR1_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR1 )
#define errMonADC_SAR_CSR1_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR1 )
#define errMonADC_SAR_CSR2_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR2 )
#define errMonADC_SAR_CSR2_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR2 )
#define errMonADC_SAR_CSR3_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR3 )
#define errMonADC_SAR_CSR3_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR3 )
#define errMonADC_SAR_CSR4_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR4 )
#define errMonADC_SAR_CSR4_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR4 )
#define errMonADC_SAR_CSR5_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR5 )
#define errMonADC_SAR_CSR5_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR5 )
#define errMonADC_SAR_CSR6_REG               (* (reg8 *) errMonADC_ADC_SAR__CSR6 )
#define errMonADC_SAR_CSR6_PTR               (  (reg8 *) errMonADC_ADC_SAR__CSR6 )
#define errMonADC_SAR_SW0_REG                (* (reg8 *) errMonADC_ADC_SAR__SW0 )
#define errMonADC_SAR_SW0_PTR                (  (reg8 *) errMonADC_ADC_SAR__SW0 )
#define errMonADC_SAR_SW2_REG                (* (reg8 *) errMonADC_ADC_SAR__SW2 )
#define errMonADC_SAR_SW2_PTR                (  (reg8 *) errMonADC_ADC_SAR__SW2 )
#define errMonADC_SAR_SW3_REG                (* (reg8 *) errMonADC_ADC_SAR__SW3 )
#define errMonADC_SAR_SW3_PTR                (  (reg8 *) errMonADC_ADC_SAR__SW3 )
#define errMonADC_SAR_SW4_REG                (* (reg8 *) errMonADC_ADC_SAR__SW4 )
#define errMonADC_SAR_SW4_PTR                (  (reg8 *) errMonADC_ADC_SAR__SW4 )
#define errMonADC_SAR_SW6_REG                (* (reg8 *) errMonADC_ADC_SAR__SW6 )
#define errMonADC_SAR_SW6_PTR                (  (reg8 *) errMonADC_ADC_SAR__SW6 )
#define errMonADC_SAR_CLK_REG                (* (reg8 *) errMonADC_ADC_SAR__CLK )
#define errMonADC_SAR_CLK_PTR                (  (reg8 *) errMonADC_ADC_SAR__CLK )
#define errMonADC_SAR_WRK0_REG               (* (reg8 *) errMonADC_ADC_SAR__WRK0 )
#define errMonADC_SAR_WRK0_PTR               (  (reg8 *) errMonADC_ADC_SAR__WRK0 )
#define errMonADC_SAR_WRK1_REG               (* (reg8 *) errMonADC_ADC_SAR__WRK1 )
#define errMonADC_SAR_WRK1_PTR               (  (reg8 *) errMonADC_ADC_SAR__WRK1 )
#define errMonADC_SAR_WRK_PTR                (  (reg16 *) errMonADC_ADC_SAR__WRK0 )
#define errMonADC_PWRMGR_SAR_REG             (* (reg8 *) errMonADC_ADC_SAR__PM_ACT_CFG )
#define errMonADC_PWRMGR_SAR_PTR             (  (reg8 *) errMonADC_ADC_SAR__PM_ACT_CFG )
#define errMonADC_STBY_PWRMGR_SAR_REG        (* (reg8 *) errMonADC_ADC_SAR__PM_STBY_CFG )
#define errMonADC_STBY_PWRMGR_SAR_PTR        (  (reg8 *) errMonADC_ADC_SAR__PM_STBY_CFG )

/* renamed registers for backward compatible */
#define errMonADC_SAR_WRK0                   errMonADC_SAR_WRK0_REG
#define errMonADC_SAR_WRK1                   errMonADC_SAR_WRK1_REG

/* This is only valid if there is an internal clock */
#if(errMonADC_DEFAULT_INTERNAL_CLK)
    /* Clock Power manager Reg */
    #define errMonADC_PWRMGR_CLK_REG         (* (reg8 *) errMonADC_theACLK__PM_ACT_CFG )
    #define errMonADC_PWRMGR_CLK_PTR         (  (reg8 *) errMonADC_theACLK__PM_ACT_CFG )
    #define errMonADC_STBY_PWRMGR_CLK_REG    (* (reg8 *) errMonADC_theACLK__PM_STBY_CFG )
    #define errMonADC_STBY_PWRMGR_CLK_PTR    (  (reg8 *) errMonADC_theACLK__PM_STBY_CFG )
#endif /*End errMonADC_DEFAULT_INTERNAL_CLK */


/**************************************
*       Register Constants
**************************************/
/* PM_ACT_CFG (Active Power Mode CFG Register) Power enable mask */
#define errMonADC_ACT_PWR_SAR_EN             (uint8)(errMonADC_ADC_SAR__PM_ACT_MSK)

/* PM_STBY_CFG (Alternate Active Power Mode CFG Register) Power enable mask */
#define errMonADC_STBY_PWR_SAR_EN            (uint8)(errMonADC_ADC_SAR__PM_STBY_MSK)

/* This is only valid if there is an internal clock */
#if(errMonADC_DEFAULT_INTERNAL_CLK)
    /* Power enable mask */
    #define errMonADC_ACT_PWR_CLK_EN         (uint8)(errMonADC_theACLK__PM_ACT_MSK)
    /* Standby power enable mask */
    #define errMonADC_STBY_PWR_CLK_EN        (uint8)(errMonADC_theACLK__PM_STBY_MSK)
#endif /*End errMonADC_DEFAULT_INTERNAL_CLK */

#if(errMonADC_IRQ_REMOVE == 0u)

    /* Priority of the ADC_SAR_IRQ interrupt. */
    #define errMonADC_INTC_PRIOR_NUMBER          (uint8)(errMonADC_IRQ__INTC_PRIOR_NUM)

    /* ADC_SAR_IRQ interrupt number */
    #define errMonADC_INTC_NUMBER                (uint8)(errMonADC_IRQ__INTC_NUMBER)

#endif   /* End errMonADC_IRQ_REMOVE */


/******************************************/
/* SAR.TR0 Trim Register 0 definitions    */
/******************************************/

/* Bit Field  SAR_CAP_TRIM_ENUM */
#define errMonADC_SAR_CAP_TRIM_MASK          (0x07u)
#define errMonADC_SAR_CAP_TRIM_0             (0x00u)    /*decrease attenuation capacitor by 0*/
#define errMonADC_SAR_CAP_TRIM_1             (0x01u)    /*decrease by 0.5 LSB*/
#define errMonADC_SAR_CAP_TRIM_2             (0x02u)    /*decrease by 2*0.5 LSB = 1 LSB*/
#define errMonADC_SAR_CAP_TRIM_3             (0x03u)    /*decrease by 3*0.5 LSB = 1.5 LSB*/
#define errMonADC_SAR_CAP_TRIM_4             (0x04u)    /*decrease by 4*0.5 LSB = 2 LSB*/
#define errMonADC_SAR_CAP_TRIM_5             (0x05u)    /*decrease by 5*0.5 LSB = 2.5 LSB*/
#define errMonADC_SAR_CAP_TRIM_6             (0x06u)    /*decrease by 6*0.5 LSB = 3 LSB*/
#define errMonADC_SAR_CAP_TRIM_7             (0x07u)    /*decrease by 7*0.5 LSB = 3.5 LSB*/

#define errMonADC_SAR_TRIMUNIT               (0x08u)    /*Increase by 6fF*/

/*******************************************************/
/* SAR.CSR0 Satatus and Control Register 0 definitions */
/*******************************************************/

/* Bit Field  SAR_ICONT_LV_ENUM */
#define errMonADC_SAR_POWER_MASK             (0xC0u)
#define errMonADC_SAR_POWER_SHIFT            (0x06u)
#define errMonADC_ICONT_LV_0                 (0x00u)
#define errMonADC_ICONT_LV_1                 (0x40u)
#define errMonADC_ICONT_LV_2                 (0x80u)
#define errMonADC_ICONT_LV_3                 (0xC0u)
#define errMonADC_ICONT_FULL_CURRENT         (0x00u)

/* Bit Field SAR_RESET_SOFT_ENUM */
#define errMonADC_SAR_RESET_SOFT_NOTACTIVE   (0x00u)
#define errMonADC_SAR_RESET_SOFT_ACTIVE      (0x20u)

/* Bit Field  SAR_COHERENCY_EN_ENUM */
#define errMonADC_SAR_COHERENCY_EN_NOLOCK    (0x00u)
#define errMonADC_SAR_COHERENCY_EN_LOCK      (0x10u)

/* Bit Field  SAR_HIZ_ENUM */
#define errMonADC_SAR_HIZ_RETAIN             (0x00u)
#define errMonADC_SAR_HIZ_CLEAR              (0x08u)

/* Bit Field SAR_MX_SOF_ENUM */
#define errMonADC_SAR_MX_SOF_BIT             (0x00u)
#define errMonADC_SAR_MX_SOF_UDB             (0x04u)

/* Bit Field SAR_SOF_MODE_ENUM */
#define errMonADC_SAR_SOF_MODE_LEVEL         (0x00u)
#define errMonADC_SAR_SOF_MODE_EDGE          (0x02u)

/* Bit Field SAR_SOF_BIT_ENUM */
#define errMonADC_SAR_SOF_STOP_CONV          (0x00u)            /* Disable conversion */
#define errMonADC_SAR_SOF_START_CONV         (0x01u)            /* Enable conversion */

/*******************************************************/
/* SAR.CSR1 Satatus and Control Register 1 definitions */
/*******************************************************/

/* Bit Field  SAR_MUXREF_ENUM */
#define errMonADC_SAR_MUXREF_MASK            (0xE0u)
#define errMonADC_SAR_MUXREF_NONE            (0x00u)
#define errMonADC_SAR_MUXREF_VDDA_2          (0x40u)
#define errMonADC_SAR_MUXREF_DAC             (0x60u)
#define errMonADC_SAR_MUXREF_1_024V          (0x80u)
#define errMonADC_SAR_MUXREF_1_20V           (0xA0u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define errMonADC_SAR_SWVP_SRC_REG           (0x00u)
#define errMonADC_SAR_SWVP_SRC_UDB           (0x10u)

/* Bit Field  SAR_SWVP_SRC_ENUM */
#define errMonADC_SAR_SWVN_SRC_REG           (0x00u)
#define errMonADC_SAR_SWVN_SRC_UDB           (0x08u)

/* Bit Field  SAR_IRQ_MODE_ENUM */
#define errMonADC_SAR_IRQ_MODE_LEVEL         (0x00u)
#define errMonADC_SAR_IRQ_MODE_EDGE          (0x04u)

/* Bit Field  SAR_IRQ_MASK_ENUM */
#define errMonADC_SAR_IRQ_MASK_DIS           (0x00u)
#define errMonADC_SAR_IRQ_MASK_EN            (0x02u)

/* Bit Field  SAR_EOF_ENUM */
#define errMonADC_SAR_EOF_0                  (0x00u)
#define errMonADC_SAR_EOF_1                  (0x01u)

/*******************************************************/
/* SAR.CSR2 Satatus and Control Register 2 definitions */
/*******************************************************/

/* Bit Field  SAR_RESOLUTION_ENUM */
#define errMonADC_SAR_RESOLUTION_MASK        (0xC0u)
#define errMonADC_SAR_RESOLUTION_SHIFT       (0x06u)
#define errMonADC_SAR_RESOLUTION_12BIT       (0xC0u)
#define errMonADC_SAR_RESOLUTION_10BIT       (0x80u)
#define errMonADC_SAR_RESOLUTION_8BIT        (0x40u)

/* Bit Field SAR_SAMPLE_WIDTH_ENUM */
#define errMonADC_SAR_SAMPLE_WIDTH_MASK      (0x3Fu)
#define errMonADC_SAR_SAMPLE_WIDTH_MIN       (0x00u)   /* minimum sample time: +1 clock cycle */
#define errMonADC_SAR_SAMPLE_WIDTH           (errMonADC_SAMPLE_PRECHARGE - 0x02u)
#define errMonADC_SAR_SAMPLE_WIDTH_MAX       (0x07u)   /* maximum sample time: +8 clock cycles */

/*******************************************************/
/* SAR.CSR3 Satatus and Control Register 3 definitions */
/*******************************************************/

/* Bit Field  SAR_EN_CP_ENUM */
#define errMonADC_SAR_EN_CP_DIS              (0x00u)
#define errMonADC_SAR_EN_CP_EN               (0x80u)

/* Bit Field  SAR_EN_RESVDA_ENUM */
#define errMonADC_SAR_EN_RESVDA_DIS          (0x00u)
#define errMonADC_SAR_EN_RESVDA_EN           (0x40u)

/* Bit Field  SAR_PWR_CTRL_VCM_ENUM */
#define errMonADC_SAR_PWR_CTRL_VCM_MASK      (0x30u)
#define errMonADC_SAR_PWR_CTRL_VCM_0         (0x00u)
#define errMonADC_SAR_PWR_CTRL_VCM_1         (0x10u)
#define errMonADC_SAR_PWR_CTRL_VCM_2         (0x20u)
#define errMonADC_SAR_PWR_CTRL_VCM_3         (0x30u)

/* Bit Field  SAR_PWR_CTRL_VREF_ENUM */
#define errMonADC_SAR_PWR_CTRL_VREF_MASK     (0x0Cu)
#define errMonADC_SAR_PWR_CTRL_VREF_0        (0x00u)
#define errMonADC_SAR_PWR_CTRL_VREF_DIV_BY2  (0x04u)
#define errMonADC_SAR_PWR_CTRL_VREF_DIV_BY3  (0x08u)
#define errMonADC_SAR_PWR_CTRL_VREF_DIV_BY4  (0x0Cu)

/* Bit Field  SAR_EN_BUF_VCM_ENUM */
#define errMonADC_SAR_EN_BUF_VCM_DIS         (0x00u)
#define errMonADC_SAR_EN_BUF_VCM_EN          (0x02u)

/* Bit Field  SAR_EN_BUF_VREF_ENUM */
#define errMonADC_SAR_EN_BUF_VREF_DIS        (0x00u)
#define errMonADC_SAR_EN_BUF_VREF_EN         (0x01u)

/*******************************************************/
/* SAR.CSR4 Satatus and Control Register 4 definitions */
/*******************************************************/

/* Bit Field  SAR_DFT_INC_ENUM */
#define errMonADC_SAR_DFT_INC_MASK           (0x0Fu)
#define errMonADC_SAR_DFT_INC_DIS            (0x00u)
#define errMonADC_SAR_DFT_INC_EN             (0x0Fu)

/* Bit Field  SAR_DFT_INC_ENUM */
#define errMonADC_SAR_DFT_OUTC_MASK          (0x70u)
#define errMonADC_SAR_DFT_OUTC_DIS           (0x00u)
#define errMonADC_SAR_DFT_OUTC_EN            (0x70u)

/*******************************************************/
/* SAR.CSR5 Satatus and Control Register 5 definitions */
/*******************************************************/

/* Bit Field  SAR_OVERRUN_DET_EN_ENUM */
#define errMonADC_SAR_OVERRUN_DET_EN_EN      (0x80u)

/* Bit Field  SAR_DLY_INC_ENUM */
#define errMonADC_SAR_DLY_INC                (0x40u)

/* Bit Field  SAR_DCEN_ENUM */
#define errMonADC_SAR_DCEN                   (0x20u)

/* Bit Field  SAR_EN_CSEL_DFT_ENUM */
#define errMonADC_SAR_EN_CSEL_DFT_DISABLED   (0x00u)
#define errMonADC_SAR_EN_CSEL_DFT_ENABLED    (0x10u)

/* Bit Field  SAR_SEL_CSEL_DFT_ENUM */
#define errMonADC_SAR_SEL_CSEL_DFT_MASK      (0x0Fu)
#define errMonADC_SAR_SEL_CSEL_DFT_MIN       (0x00u)
#define errMonADC_SAR_SEL_CSEL_DFT_MAX       (0x0Fu)
#define errMonADC_SAR_SEL_CSEL_DFT_CHAR      (0x03u)

/*******************************************************/
/* SAR.CSR6 Satatus and Control Register 6 definitions */
/*******************************************************/
#define errMonADC_INT_VREF                   (0x18u)
#define errMonADC_INT_BYPASS_EXT_VREF        (0x04u)
#define errMonADC_VDDA_VREF                  (0x80u)

/*******************************************************/
/* SAR.CSR7 Satatus and Control Register 7 definitions */
/*******************************************************/

/* Bit Field  SAR_REF_S_ENUM */
#define errMonADC_SAR_REF_S_MSB_MASK         (0x3Fu)
#define errMonADC_SAR_REF_S_MSB_DIS          (0x00u)
#define errMonADC_SAR_REF_S8_MSB_DIS         (0x01u)
#define errMonADC_SAR_REF_S9_MSB_EN          (0x02u)
#define errMonADC_SAR_REF_S10_MSB_EN         (0x04u)
#define errMonADC_SAR_REF_S11_MSB_EN         (0x08u)
#define errMonADC_SAR_REF_S12_MSB_EN         (0x10u)
#define errMonADC_SAR_REF_S13_MSB_EN         (0x20u)

/*******************************************************/
/* SAR.CLK SAR Clock Selection Register definitions    */
/*******************************************************/

/* Bit Field  MX_PUMPCLK_ENUM */
#define errMonADC_SAR_MX_PUMPCLK_MASK        (0xE0u)
#define errMonADC_SAR_MX_PUMPCLK_0           (0x00u)
#define errMonADC_SAR_MX_PUMPCLK_1           (0x20u)
#define errMonADC_SAR_MX_PUMPCLK_2           (0x40u)
#define errMonADC_SAR_MX_PUMPCLK_3           (0x60u)
#define errMonADC_SAR_MX_PUMPCLK_4           (0x80u)

/* Bit Field  BYPASS_SYNC_ENUM */
#define errMonADC_SAR_BYPASS_SYNC_0          (0x00u)
#define errMonADC_SAR_BYPASS_SYNC_1          (0x10u)

/* Bit Field  MX_CLK_EN_ENUM */
#define errMonADC_SAR_MX_CLK_EN              (0x08u)

/* Bit Field  MX_CLK_ENUM  */
#define errMonADC_SAR_MX_CLK_MASK            (0x07u)
#define errMonADC_SAR_MX_CLK_0               (0x00u)
#define errMonADC_SAR_MX_CLK_1               (0x01u)
#define errMonADC_SAR_MX_CLK_2               (0x02u)
#define errMonADC_SAR_MX_CLK_3               (0x03u)
#define errMonADC_SAR_MX_CLK_4               (0x04u)

/*********************************************************/
/* ANAIF.WRK.SARS.SOF SAR Global Start-of-frame register */
/*********************************************************/

/* Bit Field  SAR_SOF_BIT_ENUM */
#define errMonADC_SAR_SOFR_BIT_MASK          (0x03u)
#define errMonADC_SAR_SOFR_BIT_0             (0x00u)
#define errMonADC_SAR_SOFR_BIT_1             (0x01u)

/***********************************************/
/* SAR.SW3 SAR Analog Routing Register 3       */
/***********************************************/
#define errMonADC_SAR_VP_VSSA                (0x04u)
#define errMonADC_SAR_VN_AMX                 (0x10u)
#define errMonADC_SAR_VN_VREF                (0x20u)
#define errMonADC_SAR_VN_VSSA                (0x40u)
#define errMonADC_SAR_VN_MASK                (0x60u)

/***********************************************/
/* SAR.WRKx SAR Working Register               */
/***********************************************/
#define errMonADC_SAR_WRK_MAX                (0xFFFu)
#define errMonADC_SAR_DIFF_SHIFT             (0x800u)

/* Absolute maximum counts equivalent reference voltage */
#define errMonADC_SAR_WRK_MAX_12BIT          (0x00001000Lu)
#define errMonADC_SAR_WRK_MAX_10BIT          (0x00000400Lu)
#define errMonADC_SAR_WRK_MAX_8BIT           (0x00000100Lu)


#endif /* End CY_ADC_SAR_errMonADC_H */


/* [] END OF FILE */
