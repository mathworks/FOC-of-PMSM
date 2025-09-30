/*-----------------------------------------------------------------------------
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/
/*******************************************************************************
*
* @file     gd3000_init.c
*
* @date     Jul-9-2021
*
* @brief    MC34GD3000 Initialization
*
*******************************************************************************/
/*******************************************************************************
* Includes
*******************************************************************************/
#include "gd3000_init.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
tpp_drv_config_t  tppDrvConfig;   /* GD3000 configuration structure */

/*******************************************************************************
*
* Function:     status_t GD3000_Init(void)
*
* Description:  This function initialize MC34GD3000 MOSFET pre-driver.
*               MC34GD3000 SW driver uses S32K344 LPSPI1 module as a communication
*               interface to configure MC34GD3000 operation mode and to track MC34GD3000
*               Status0/Status1 registers.
*
*******************************************************************************/
status_t GD3000_Init(void)
{
    /* Local Variables */
    status_t GDInitErr = kStatus_Success;

   /* GD3000 pin configuration */
    tppDrvConfig.en1PinIndex    = AML_GD_EN1EN2_PIN;
    tppDrvConfig.en1PinInstance = AML_GD_EN1EN2_PORT;
    tppDrvConfig.en2PinIndex    = AML_GD_EN1EN2_PIN;
    tppDrvConfig.en2PinInstance = AML_GD_EN1EN2_PORT;
    tppDrvConfig.rstPinIndex    = AML_GD_RST_PIN;
    tppDrvConfig.rstPinInstance = AML_GD_RST_PORT;

    /* GD3000 device configuration */
    tppDrvConfig.deviceConfig.deadtime =    INIT_DEADTIME;
    tppDrvConfig.deviceConfig.intMask0 =    INIT_INTERRUPTS0;
    tppDrvConfig.deviceConfig.intMask1 =    INIT_INTERRUPTS1;
    tppDrvConfig.deviceConfig.modeMask =    INIT_MODE;

    /* GD3000 status registers configuration */
    tppDrvConfig.deviceConfig.statusRegister[0U] = 0U;
    tppDrvConfig.deviceConfig.statusRegister[1U] = 0U;
    tppDrvConfig.deviceConfig.statusRegister[2U] = 0U;
    tppDrvConfig.deviceConfig.statusRegister[3U] = 0U;

    /* GD3000 SPI configuration */
    tppDrvConfig.csPinIndex = AML_GD_SPI_PCS_PIN;
    tppDrvConfig.csPinInstance = AML_GD_SPI_PCS_PORT;
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    /* Initialize Peripherals:
     * The code below only applies to Kinetis SDK and S32K1 SDK.
     * When S32K3 RTD is used, the peripherals (GPIO and SPI) are configured
     * through RTD APIs. */
    tppDrvConfig.spiInstance = AML_GD_SPI_INST;
    tppDrvConfig.spiTppConfig.baudRateHz =    LPSPI_FREQ;
    tppDrvConfig.spiTppConfig.sourceClockHz = 4000000U;
    TPP_ConfigureGpio(&tppDrvConfig);
    TPP_ConfigureSpi(&tppDrvConfig, NULL);
#endif

    GDInitErr = TPP_Init(&tppDrvConfig, tppModeEnable);

    return GDInitErr;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : TPP_InitializeOutputs
 * Description   : This function initialize output of the MC34GD3000 MOSFET Pre-driver.
 *
 *END**************************************************************************/
void TPP_InitializeOutputs (void)
{
    /* ********************************************************************
     *
     *The function is called by TPP_Init during the initialization process and
     *it is responsible for proper initialization of pins selected for GD3000.
     *Please see MC34GD3000 Product data sheet (Rev. 6.0) for more details about
     *GD3000 initialization procedure. In this example all necessary initialization
     *(SIUL and LCU peripheral) is covered by Lcu_Ip_Init and Siul2_Port_Ip_Initfunctions
     * so no additional configuration is needed in this place.
     *
     * *********************************************************************/
}
