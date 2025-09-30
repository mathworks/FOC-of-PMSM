/*-----------------------------------------------------------------------------
* Copyright 2013-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/

/*!
 * @file common_aml.h
 *
 *  Constants and types definition common for AML drivers.
 */

#ifndef SOURCE_COMMON_AML_H_
#define SOURCE_COMMON_AML_H_

 /*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include "assert.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @addtogroup macro_group
 * @{
 */
/*! @brief SDK versions supported by AML layer. */
#define KINETIS_SDK_2_0       0U              /*! Kinetis SDK 2.0. */
#define S32K1_SDK_3_0_0       1U              /*! S32K1 SDK 3.0.0. */
#define S32K1_RTD_LLD_x_x_x   2U              /*! Reserved for S32K1 RTD LLD(Low Level Driver) x.x.x.*/
#define S32K1_RTD_MCAL_x_x_x  3U              /*! Reserved for S32K1 RTD MCAL x.x.x.*/
#define S32K3_RTD_LLD         4U              /*! S32K3 RTD LLD. */
#define S32K3_RTD_MCAL        5U              /*! S32K3 RTD MCAL. */

/*!
 * @brief Selection of SDK version you are using (S32K1 SDK/RTD, Kinetis SDK 2.0 or S32K3 RTD).
 *
 * Use macros defined above (S32K1 SDK/RTD, Kinetis SDK 2.0 or S32K3 RTD).
 */
#define SDK_VERSION S32K3_RTD_MCAL

/*!
 * @brief Unused variable. This macro is used when some variable is not used in SDK.
 */
#define AML_UNUSED(x) (void)(x)

#if (SDK_VERSION == KINETIS_SDK_2_0)

/* Definition of error codes. */
#include "fsl_common.h"

#endif

/*!
 * @brief Default Pin settings.
 *
 * According to the configured Pins in Kinetis SDK, S32K1 SDK or S32K3 RTD, user should
 * specify the default Pins for GD3000 here.
 * */

#if (SDK_VERSION == KINETIS_SDK_2_0)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K1_SDK_3_0_0)

/* Specify the default Pins for GD3000. */
#define AML_GD_EN1EN2_PIN    (2U)
#define AML_GD_EN1EN2_PORT   instanceA
#define AML_GD_RST_PIN       (3U)
#define AML_GD_RST_PORT      instanceA
#define AML_GD_SPI_PCS_PIN   (5U)
#define AML_GD_SPI_PCS_PORT  instanceB

#endif

#if (SDK_VERSION == S32K1_RTD_LLD_x_x_x)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K1_RTD_MCAL_x_x_x)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K3_RTD_LLD)

/* Specify the default Pins for GD3000. */
#define AML_GD_EN1EN2_PIN    GD_EN1EN2_PIN
#define AML_GD_EN1EN2_PORT   ((uint32_t)(uint32_t *)GD_EN1EN2_PORT)
#define AML_GD_RST_PIN       GD_RST_PIN
#define AML_GD_RST_PORT      ((uint32_t)(uint32_t *)GD_RST_PORT)
#define AML_GD_SPI_PCS_PIN   GD_SPI_PCS_PIN
#define AML_GD_SPI_PCS_PORT  ((uint32_t)(uint32_t *)GD_SPI_PCS_PORT)

#endif

#if (SDK_VERSION == S32K3_RTD_MCAL)

/* Specify the default Pins for GD3000. */
#define AML_GD_EN1EN2_PIN    (DioConf_DioChannel_GD_EN)
#define AML_GD_EN1EN2_PORT   (0U)
#define AML_GD_RST_PIN       (DioConf_DioChannel_GD_RST)
#define AML_GD_RST_PORT      (0U)
#define AML_GD_SPI_PCS_PIN   (DioConf_DioChannel_GD_CS)
#define AML_GD_SPI_PCS_PORT  (0U)

#endif

/*!
 * @brief Default SPI settings.
 *
 * According to the configured SPI in Kinetis SDK, S32K1 SDK or S32K3 RTD, user should
 * specify the default SPI for GD3000 here.
 * */

#if (SDK_VERSION == KINETIS_SDK_2_0)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K1_SDK_3_0_0)

/* Specify the default device of used LPSPIfor GD3000. */
#define AML_GD_SPI_INST      (0U)

#endif

#if (SDK_VERSION == S32K1_RTD_LLD_x_x_x)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K1_RTD_MCAL_x_x_x)

/* Specify the default Pins for GD3000. */
/* Reserved */

#endif

#if (SDK_VERSION == S32K3_RTD_LLD)

/* Specify the default device of used LPSPIfor GD3000. */
#define AML_SPI_Device Lpspi_Ip_DeviceAttributes_SpiExternalDevice_0_BOARD_InitPeripherals

#endif

#if (SDK_VERSION == S32K3_RTD_MCAL)

/* Specify the ID of SPI Channel used for GD3000. */
#define AML_SPI_CHANNEL_ID  0
/* Specify the ID of SPI External Device used for GD3000. */
#define AML_SPI_DEVICE_ID   0
/* Specify the ID of SPI job used for GD3000. */
#define AML_SPI_JOB_ID      0
/* Specify the ID of SPI Sequence used for GD3000. */
#define AML_SPI_SEQUENCE_ID 0
/* Specify the ID of SPI Phy used for GD3000. */
#define AML_SPI_PHY_ID      0

#endif

/*! @brief Assertion settings. */

#if (SDK_VERSION == KINETIS_SDK_2_0)

/* #define NDEBUG */                /*!< Uncomment this macro to disable assertions in SDK 2.0. */

/*! @brief Assert function for SDK 2.0. */
#define AML_ASSERT(condition) \
    (assert(condition))

#elif (SDK_VERSION == S32K1_SDK_3_0_0)

//#define DEV_ERROR_DETECT            /*!< Comment this macro to disable assertions in SDK S32. */

/*! @brief Assert function for SDK 2.0. */
#define AML_ASSERT(condition) \
    (DEV_ASSERT(condition))

#elif (SDK_VERSION == S32K3_RTD_LLD || SDK_VERSION == S32K3_RTD_MCAL)
#include "Devassert.h"

//#define DEV_ERROR_DETECT            /*!< Comment this macro to disable assertions in RTD 0.9.0. */

/*! @brief Assert function for RTD 0.9.0. */
#define AML_ASSERT(condition) (DevAssert(condition))

#endif

#if  (SDK_VERSION == S32K1_SDK_3_0_0 \
   || SDK_VERSION == S32K3_RTD_LLD \
   || SDK_VERSION == S32K3_RTD_MCAL)

/*! @brief Construct a status code value from a group and code number. This
 * code is taken from SDK 2.0. */
#define MAKE_STATUS(group, code) ((((group) * 100U) + (code)))

#endif
/*! @} */

/*!
 * @addtogroup enum_group
 * @{
 */
#if  (SDK_VERSION == S32K1_SDK_3_0_0 \
   || SDK_VERSION == S32K3_RTD_LLD \
   || SDK_VERSION == S32K3_RTD_MCAL)

#if (SDK_VERSION == S32K1_SDK_3_0_0)
#include "status.h"
#endif

/*! @brief Status group numbers. This code is taken from SDK 2.0. */
enum _status_groups
{
    kStatusGroup_Generic = 0,                 /*!< Group number for generic status codes. */
    kStatusGroup_LPSPI = 4,                   /*!< Group number for LPSPI status codes. */
    kStatusGroup_FLEXIO_SPI = 5,              /*!< Group number for FLEXIO SPI status codes. */
    kStatusGroup_DSPI = 6,                    /*!< Group number for DSPI status codes. */
    kStatusGroup_FLEXIO_UART = 7,             /*!< Group number for FLEXIO UART status codes. */
    kStatusGroup_FLEXIO_I2C = 8,              /*!< Group number for FLEXIO I2C status codes. */
    kStatusGroup_LPI2C = 9,                   /*!< Group number for LPI2C status codes. */
    kStatusGroup_UART = 10,                   /*!< Group number for UART status codes. */
    kStatusGroup_I2C = 11,                    /*!< Group number for UART status codes. */
    kStatusGroup_LPSCI = 12,                  /*!< Group number for LPSCI status codes. */
    kStatusGroup_LPUART = 13,                 /*!< Group number for LPUART status codes. */
    kStatusGroup_SPI = 14,                    /*!< Group number for SPI status code.*/
    kStatusGroup_SDSPI = 22,                  /*!< Group number for SDSPI status codes. */
    kStatusGroup_FLEXIO_I2S = 23,             /*!< Group number for FLEXIO I2S status codes */
    kStatusGroup_PHY = 41,                    /*!< Group number for PHY status codes. */
    kStatusGroup_TRGMUX = 42,                 /*!< Group number for TRGMUX status codes. */
    kStatusGroup_QSPI = 45,                   /*!< Group number for QSPI status codes. */
    kStatusGroup_DMA = 50,                    /*!< Group number for DMA status codes. */
    kStatusGroup_EDMA = 51,                   /*!< Group number for EDMA status codes. */
    kStatusGroup_DMAMGR = 52,                 /*!< Group number for DMAMGR status codes. */
    kStatusGroup_FLEXCAN = 53,                /*!< Group number for FlexCAN status codes. */
    kStatusGroup_ApplicationRangeStart = 100, /*!< Starting number for application groups. */
};

/*! @brief Generic status return codes. This code is taken from SDK 2.0. */
enum _generic_status
{
    kStatus_Success = MAKE_STATUS(kStatusGroup_Generic, 0),
    kStatus_Fail = MAKE_STATUS(kStatusGroup_Generic, 1),
    kStatus_ReadOnly = MAKE_STATUS(kStatusGroup_Generic, 2),
    kStatus_OutOfRange = MAKE_STATUS(kStatusGroup_Generic, 3),
    kStatus_InvalidArgument = MAKE_STATUS(kStatusGroup_Generic, 4),
    kStatus_Timeout = MAKE_STATUS(kStatusGroup_Generic, 5),
    kStatus_NoTransferInProgress = MAKE_STATUS(kStatusGroup_Generic, 6),
};

/*! @brief Type used for all status and error return values. This code is
 * taken from SDK 2.0. This status is returned from AML but
 * SDK32 driver returns status_t from status.h file. AML need to be compatible 
 * with older existing drivers. Be careful if use status from AML or 
 * SDK32 driver directly. This was done because SDK32 modify
 * status to same name as AML layer.
 *  */

#define status_t aml_status_t
typedef int32_t status_t;

#endif /* END of S32 SDK specific enumerations. */

/* Additional error values. */
enum aml_groups{
    kStatusGroup_AML_SPI = 101,
    kStatusGroup_AML_TMR = 102,
    kStatusGroup_AML_I2C = 103,
    kStatusGroup_AML_GPIO = 104,
    kStatusGroup_Reserved = 110,
    kStatusGroup_ValveDriver = 111, /* Valve Controller */
    kStatusGroup_SHB = 112,         /* SPI H-Bridge */
    kStatusGroup_SF = 113,          /* Sigfox */
    kStatusGroup_LZ = 114,          /* Lizard */
    kStatusGroup_TPP = 115,         /* Three Phase Predriver */
    kStatusGroup_MVHB = 116,        /* Medium Voltage H-Bridge */
    kStatusGroup_LVHB = 117,        /* Low Voltage H-Bridge */
    kStatusGroup_BCC = 118,         /* Battery Cell Controller */
    kStatusGroup_ASL = 119,         /* Boost/Buck Converters */
    kStatusGroup_FS65 = 120,        /* FS65/45 SBC. */
};
/*! @} */

/*! @brief Type for peripheral instance number. */
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)

typedef uint8_t aml_port_t;
typedef uint8_t aml_instance_t;

#elif (SDK_VERSION == S32K3_RTD_LLD)

typedef uint32_t aml_port_t;
typedef uint32_t aml_instance_t;

#elif (SDK_VERSION == S32K3_RTD_MCAL)

typedef uint16_t aml_port_t;
typedef uint16_t aml_instance_t;

#endif

#endif /* SOURCE_COMMON_AML_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
