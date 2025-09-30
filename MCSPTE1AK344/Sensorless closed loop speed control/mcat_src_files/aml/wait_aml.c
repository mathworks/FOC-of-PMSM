/*-----------------------------------------------------------------------------
* Copyright 2013-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/

/*
 * File: wait_aml.c
 *
 * This driver creates abstraction for WAIT functions for S32K1 SDK/RTD,
 * Kinetis SDK 2.0 or S32K3 RTD.
 */

/*******************************************************************************
* Includes
 ******************************************************************************/
#include "wait_aml.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : WAIT_AML_GetSysFreq
 * Description   : Get system core frequency in ticks
 *
 *END**************************************************************************/
inline uint32_t WAIT_AML_GetSysFreq( void )
{
    uint32_t freq;
#if (SDK_VERSION == S32K1_SDK_3_0_0)
    CLOCK_SYS_GetFreq(CORE_CLK, &freq);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    freq = Clock_Ip_GetClockFrequency(CORE_CLK);
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    freq = Mcu_GetClockFrequency(CORE_CLK);
#endif
    return freq;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : WAIT_AML_WaitCycles
 * Description   : Waits for specified amount of cycles which is given by 32bit 
 *                 value range. Assumption for this function is that target 
 *                 architecture is using 32bit general purpose registers.
 *
 *END**************************************************************************/
void WAIT_AML_WaitCycles(uint32_t cycles)
{
    /* Advance to next multiple of 4. Value 0x04U ensures that the number
     * is not zero. */
    cycles = (cycles & 0xFFFFFFFCU) | 0x04U;
    WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : WAIT_AML_WaitSec
 * Description   : Waits for specified amount of seconds.
 *
 *END**************************************************************************/
void WAIT_AML_WaitSec(uint16_t delay)
{
    for (; delay > 0U; delay--) {
        WAIT_AML_WaitMs(1000U);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : WAIT_AML_WaitMs
 * Description   : Waits for specified amount of milliseconds.
 *
 *END**************************************************************************/
void WAIT_AML_WaitMs(uint16_t delay)
{
    uint32_t cycles = (uint32_t) WAIT_AML_GET_CYCLES_FOR_MS(delay, WAIT_AML_SYSTEM_CLOCK_FREQ );

    /* Advance to multiple of 4. */
    cycles = (cycles & 0xFFFFFFFCU) | 0x04U;;
    WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : WAIT_AML_WaitUs
 * Description   : Waits for specified amount of microseconds.
 *
 *END**************************************************************************/
void WAIT_AML_WaitUs(uint16_t delay)
{
    uint32_t cycles = (uint32_t) WAIT_AML_GET_CYCLES_FOR_US(delay, WAIT_AML_SYSTEM_CLOCK_FREQ );

    /* Advance to next multiple of 4. Value 0x04U ensures that the number
     * is not zero. */
    cycles = (cycles & 0xFFFFFFFCU) | 0x04U;
    WAIT_AML_WAIT_FOR_MUL4_CYCLES(cycles);
}



/*******************************************************************************
 * EOF
 ******************************************************************************/
