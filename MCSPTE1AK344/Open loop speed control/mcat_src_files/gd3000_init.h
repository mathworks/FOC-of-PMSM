/*-----------------------------------------------------------------------------
* Copyright 2006-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/
/*******************************************************************************
*
* @file     gd3000_init.h
*
* @date     Jul-9-2021
*
* @brief    MC34GD3000 Initialization
*
*******************************************************************************/
#ifndef GD3000_GD3000_INIT_H_
#define GD3000_GD3000_INIT_H_
/*******************************************************************************
* Includes
*******************************************************************************/
#include "common_aml.h"
#include "gpio_aml.h"
#include "tpp.h"

/*******************************************************************************
* Constants and macros
*******************************************************************************/
/* Frequency of SPI communication with device in Hz. */
#define LPSPI_FREQ         2000000
/* Device interrupt masks set by MASK0 and MASK1 commands. */
#define INIT_INTERRUPTS0 (TPP_MASK0_OT_INT_ENABLED | TPP_MASK0_DES_INT_ENABLED | \
                          TPP_MASK0_UV_INT_ENABLED | TPP_MASK0_OC_INT_ENABLED)
#define INIT_INTERRUPTS1 (TPP_MASK1_PHS_INT_ENABLED | TPP_MASK1_FRM_INT_ENABLED | \
                          TPP_MASK1_WRT_INT_ENABLED | TPP_MASK1_RST_INT_ENABLED)
/* Device configuration set by Mode command. */
#ifdef S32K396
#define INIT_MODE        (TPP_MODE_DESF_ENABLED | TPP_MODE_FULL_DISABLED | TPP_MODE_LOCK_DISABLED)
#else
#define INIT_MODE        (TPP_MODE_DESF_DISABLED | TPP_MODE_FULL_ENABLED | TPP_MODE_LOCK_ENABLED)
#endif

/* Dead time of device in nanoseconds. */
#ifdef S32K396
#define INIT_DEADTIME    650
#else
#define INIT_DEADTIME    500
#endif

extern tpp_drv_config_t tppDrvConfig;

/*******************************************************************************
* Global function prototypes
*******************************************************************************/
status_t GD3000_Init(void);

#endif /* GD3000_GD3000_INIT_H_ */
