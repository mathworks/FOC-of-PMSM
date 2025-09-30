/*-----------------------------------------------------------------------------
* Copyright 2013-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/

/*!
 * @file wait_aml.h
 *
 * This driver creates abstraction for WAIT functions for S32K1 SDK/RTD,
 * Kinetis SDK 2.0 or S32K3 RTD.
 */

#ifndef SOURCE_WAIT_AML_H_
#define SOURCE_WAIT_AML_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "common_aml.h"

#if (SDK_VERSION == KINETIS_SDK_2_0)
#include "fsl_clock.h"
#elif (SDK_VERSION == S32K1_SDK_3_0_0)
#include "device_registers.h"
#include "clock_manager.h"
#elif (SDK_VERSION == S32K3_RTD_LLD)
#include "Clock_Ip.h"
#include "Osif.h"
#elif (SDK_VERSION == S32K3_RTD_MCAL)
#include "Mcu.h"
#include "Osif.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @addtogroup macro_group
 * @{
 */
#if (SDK_VERSION == KINETIS_SDK_2_0)
#define WAIT_AML_SYSTEM_CLOCK_FREQ   (CLOCK_GetCoreSysClkFreq())
#elif (SDK_VERSION == S32K1_SDK_3_0_0 \
    || SDK_VERSION == S32K3_RTD_LLD \
    || SDK_VERSION == S32K3_RTD_MCAL)
#define WAIT_AML_SYSTEM_CLOCK_FREQ   (WAIT_AML_GetSysFreq())
#endif

#define WAIT_AML_GET_CYCLES_FOR_MS(ms, freq) (((freq) / 1000U) * (ms))            /*!< Gets needed cycles for specified delay in milliseconds, calculation is based on core clock frequency. */
#define WAIT_AML_GET_CYCLES_FOR_US(us, freq) (((freq) / 1000U) * (us) / 1000U)    /*!< Gets needed cycles for specified delay in microseconds, calculation is based on core clock frequency. */
#define WAIT_AML_GET_CYCLES_FOR_NS(ns, freq) (((freq) / 1000000U) * (ns) / 1000U) /*!< Gets needed cycles for specified delay in nanoseconds, calculation is based on core clock frequency. */
/*! @} */

#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
#if defined(__thumb__) && !defined(__thumb2__) /* Thumb instruction set only */
/*!
 * @brief Waits for exact number of cycles which can be expressed as multiple of 4.
 *
 * MOV - 1 cycle
 * SUB - 1 cycle
 * BNE - 1 cycle or 2 cycles if jump is realized
 *
 * Output list (empty) - which registers are output and how to map them to C code.
 * Input list (Cycles) - which registers are input and how to map them to C code.
 * Clobber list (r0, r1, cc) - which registers might have changed during
 * execution of asm code (compiler will have to reload them).
 *
 * @param Cycles | Number of cycles to wait.
 */
#define WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles) \
  __asm( \
    "mov r0, %[cycles] \n\t" \
    "0: \n\t"                \
      "sub r0, #4 \n\t"      \
      "nop \n\t"             \
    "bne 0b \n\t"            \
     :                       \
     : [cycles] "r" (cycles) \
     : "r0", "r1", "cc"      \
  )
  
#else /* Thumb2 or A32 instruction set */

/*!
 * @brief Waits for exact number of cycles which can be expressed as multiple of 4.
 *
 * @param Cycles | Number of cycles to wait.
 */
#define WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles) \
  __asm( \
    "movs r0, %[cycles] \n"  \
    "0: \n"                  \
      "subs r0, r0, #4 \n"   \
      "nop \n\t"             \
    "bne 0b \n"              \
     :                       \
     : [cycles] "r" (cycles) \
     : "r0", "r1", "cc"      \
  )
#endif

#elif (SDK_VERSION == S32K3_RTD_LLD || SDK_VERSION == S32K3_RTD_MCAL)

#if OSIF_USE_SYSTEM_TIMER == STD_ON
/*!
 * @brief Waits for exact number of cycles which can be expressed as multiple of 4.
 *
 * @param Cycles | Number of cycles to wait.
 */
static inline void WAIT_AML_WAIT_FOR_MUL4_CYCLES (uint32 cycles)
{
    uint32 cntRef, cntTimeout = 0;
    cntRef = OsIf_GetCounter(OSIF_COUNTER_SYSTEM);
    while(cntTimeout < cycles){
        cntTimeout += OsIf_GetElapsed(&cntRef, OSIF_COUNTER_SYSTEM);
    }
}
#else
 /*!
  * @brief Waits for exact number of cycles which can be expressed as multiple of 4.
  *
  * @param Cycles | Number of cycles to wait.
  */
#define WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles) \
  __asm( \
    "movs r0, %[cycles] \n"  \
    "0: \n"                  \
      "subs r0, r0, #4 \n"   \
      "nop \n\t"             \
    "bne 0b \n"              \
     :                       \
     : [cycles] "r" (cycles) \
     : "r0", "r1", "cc"      \
  )

#endif

#endif

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @addtogroup function_group
 * @{
 */ 
/*!
 * @brief Waits for specified amount of cycles which is given by 32bit 
 *        value range. Assumption for this function is that target 
 *        architecture is using 32bit general purpose registers.
 * 
 * @param cycles - Number of cycles to wait.
 */
void WAIT_AML_WaitCycles(uint32_t cycles);

/*!
 * @brief Waits for specified amount of seconds.
 *
 * @param delay - Number of seconds to wait.
 */
void WAIT_AML_WaitSec(uint16_t delay);

/*!
 * @brief Waits for specified amount of milliseconds.
 *
 * @param delay - Number of milliseconds to wait.
 */
void WAIT_AML_WaitMs(uint16_t delay);

/*!
 * @brief Waits for specified amount of microseconds.
 *
 * @param delay - Number of microseconds to wait.
 */
void WAIT_AML_WaitUs(uint16_t delay);
/*! @} */

/*!
 * @brief Returns the core clock system value in ticks.
 */
uint32_t WAIT_AML_GetSysFreq( void );

#endif /* SOURCE_WAIT_AML_H_ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
