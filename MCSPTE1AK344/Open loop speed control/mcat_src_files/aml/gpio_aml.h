/*-----------------------------------------------------------------------------
* Copyright 2013-2021 NXP
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
*-----------------------------------------------------------------------------*/

/*!
 * @file gpio_aml.h
 *
 * This driver creates abstraction for GPIO for KSDK 2.0, S32K1 SDK and S32K3 RTD.
 */

#ifndef SOURCE_MIDDLEWARE_GPIO_H_
#define SOURCE_MIDDLEWARE_GPIO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "common_aml.h"

#if (SDK_VERSION == S32K1_SDK_3_0_0)
#include "Cpu.h"
#include "pin_mux.h"
#include "device_registers.h"
#elif (SDK_VERSION == KINETIS_SDK_2_0)
#include "fsl_common.h"
#include "fsl_gpio.h"
#elif (SDK_VERSION == S32K3_RTD_LLD)
#include "Siul2_Port_Ip.h"
#include "Siul2_Dio_Ip.h"
#elif (SDK_VERSION == S32K3_RTD_MCAL)
#include "Platform.h"
#include "Port.h"
#include "Dio.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @addtogroup enum_group
 * @{
 */
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
 /*! @brief Instance of GPIO peripheral (GPIO A = instanceA). */ 
typedef enum 
{
    instanceA = 0U,                 /*!< GPIO A. */
    instanceB,                      /*!< GPIO B. */
    instanceC,                      /*!< GPIO C. */
    instanceD,                      /*!< GPIO D. */
    instanceE,                      /*!< GPIO E. */
    instanceF,                      /*!< GPIO F. */
    instanceG,                      /*!< GPIO G. */
    instanceH,                      /*!< GPIO H. */
    instanceI                       /*!< GPIO I. */
} gpio_aml_instance_t;
#endif

/*! @brief GPIO peripheral direction. */
typedef enum 
{
    gpioDirDigitalInput = 0U,  /*!< Set current pin as digital input. */
    gpioDirDigitalOutput = 1U  /*!< Set current pin as digital output. */
} gpio_aml_pin_direction_t;
 /*! @} */

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
/*! @brief Pointers to GPIO bases for each instance. */
static GPIO_Type *const g_gpioBases[] = GPIO_BASE_PTRS;
/*! @brief Pointers to port bases for each instance. */
static PORT_Type *const g_portBases[] = PORT_BASE_PTRS;
#endif

/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @addtogroup function_group
 * @{
 */  
#if (SDK_VERSION == S32K1_SDK_3_0_0)
/*!
 * @brief   Installs user defined interrupt handler.
 *
 * @param   irq         Interrupt request number.
 * @param   irqHandler  Pointer to user defined  interrupt handler.
 */
static inline void AML_GPIO_InstallHandler(IRQn_Type irq, void (*irqHandler)(void))
{
    INT_SYS_EnableIRQ(irq);
    INT_SYS_InstallHandler(irq, irqHandler, NULL);
}
#elif (SDK_VERSION == KINETIS_SDK_2_0)
/*!
 * @brief   Installs user defined interrupt handler.
 *
 * @param   irq         Interrupt request number.
 * @param   irqHandler  Address of user defined interrupt handler.
 */
static inline void AML_GPIO_InstallHandler(IRQn_Type irq, uint32_t irqHandler)
{
    InstallIRQHandler(irq, irqHandler);
    EnableIRQ(irq);
}
#elif (SDK_VERSION == S32K3_RTD_LLD)
/*!
 * @brief   Installs user defined interrupt handler.
 *
 * @param   irq         Interrupt request number.
 * @param   irqHandler  Address of user defined interrupt handler.
 */
static inline void AML_GPIO_InstallHandler(IRQn_Type irq, void (*irqHandler)(void))
{
    /* Please configure Handler through CT and RTD drivers when S32K3 LLD is used. */
    AML_UNUSED(irq);
    AML_UNUSED(irqHandler);
}
#elif (SDK_VERSION == S32K3_RTD_MCAL)
/*!
 * @brief   Installs user defined interrupt handler.
 *
 * @param   irq         Interrupt request number.
 * @param   irqHandler  Address of user defined interrupt handler.
 */
static inline void AML_GPIO_InstallHandler(IRQn_Type irq, const Platform_IrqHandlerType irqHandler)
{
    /* Please configure Handler through CT and RTD drivers when S32K3 MCAL is used. */
    AML_UNUSED(irq);
    AML_UNUSED(irqHandler);
}
#endif

/*!
 * @brief   Sets output pin to '1' or '0'.
 *
 * @param   port        Port of GPIO peripheral.
 * @param   pinIndex    Number of GPIO pin to be set.
 * @param   outputValue Value to be written to GPIO output pin, '1' or '0'.
 */
static inline void GPIO_AML_WriteOutput(aml_port_t port, uint8_t pinIndex, uint8_t outputValue)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    (outputValue == 0U) ? (g_gpioBases[port]->PCOR = 1U << pinIndex) : 
            (g_gpioBases[port]->PSOR = 1U << pinIndex);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    Siul2_Dio_Ip_WritePin((Siul2_Dio_Ip_GpioType *)port, pinIndex, outputValue);
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    AML_UNUSED(port);
    Dio_WriteChannel((Dio_ChannelType)(pinIndex), (Dio_LevelType)outputValue);
#endif
}

/*!
 * @brief   Sets output pin to '1'.
 *
 * @param   port        Port of GPIO peripheral.
 * @param   pinIndex    Number of GPIO pin to be set.
 */
static inline void GPIO_AML_SetOutput(aml_port_t port, uint8_t pinIndex)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    g_gpioBases[port]->PSOR = (uint32_t)(1U << pinIndex);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    Siul2_Dio_Ip_SetPins((Siul2_Dio_Ip_GpioType *)port, (uint16)(1 << pinIndex));
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    AML_UNUSED(port);
    Dio_WriteChannel((Dio_ChannelType)(pinIndex), (Dio_LevelType)STD_ON);
#endif
}

/*!
 * @brief   Clears output pin. Sets it to '0'.
 *
 * @param   port        Port of GPIO peripheral.
 * @param   pinIndex    Number of GPIO pin to be cleared.
 */
static inline void GPIO_AML_ClearOutput(aml_port_t port, uint8_t pinIndex)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    g_gpioBases[port]->PCOR = (uint32_t)(1U << pinIndex);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    Siul2_Dio_Ip_ClearPins((Siul2_Dio_Ip_GpioType *)port, (uint16)(1 << pinIndex));
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    AML_UNUSED(port);
    Dio_WriteChannel((Dio_ChannelType)(pinIndex), (Dio_LevelType)STD_OFF);
#endif
}

/*!
 * @brief   Toggles output pin.
 *
 * @param   port        Port of GPIO peripheral.
 * @param   pinIndex    Number of GPIO pin to be toggled.
 */
static inline void GPIO_AML_ToggleOutput(aml_port_t port, uint8_t pinIndex)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    g_gpioBases[port]->PTOR = (uint32_t)(1U << pinIndex);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    Siul2_Dio_Ip_TogglePins((Siul2_Dio_Ip_GpioType *)port, (uint16)(1 << pinIndex));
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    AML_UNUSED(port);
    Dio_FlipChannel((Dio_ChannelType)(pinIndex));
#endif
}

/*!
 * @brief   Returns value of input pin.
 *
 * @param   port        Port of GPIO peripheral.
 * @param   pinIndex    Number of GPIO pin to be read.
 *
 * @return  Value of input pin (0 - low, 1 - high).
 */
static inline uint32_t GPIO_AML_ReadInput(aml_port_t port, uint8_t pinIndex)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    return (((g_gpioBases[port]->PDIR) >> pinIndex) & 1U);
#elif (SDK_VERSION == S32K3_RTD_LLD)
    return (uint32_t)Siul2_Dio_Ip_ReadPin((Siul2_Dio_Ip_GpioType *)port, pinIndex);
#elif (SDK_VERSION == S32K3_RTD_MCAL)
    AML_UNUSED(port);
    return Dio_ReadChannel((Dio_ChannelType)(pinIndex));
#endif
}

/*!
 * @brief   Returns interrupt flags of whole port, e.g. PORTA. Returned value
 *          needs to be masked in order to find out the interrupt source.
 *          If configured for a level sensitive interrupt that remains asserted,
 *          the flag is set again immediately.
 *
 * @param   port        Port of PORT.
 *
 * @return  Interrupt flags of desired port.
 */
static inline uint32_t GPIO_AML_GetInterruptFlags(aml_port_t port)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    return g_portBases[port]->ISFR;
#elif (SDK_VERSION == S32K3_RTD_LLD ||SDK_VERSION == S32K3_RTD_MCAL)
    /* Please get interrupt flags through RTD APIs when S32K3 RTD LLD and MCAL is used. */
    AML_UNUSED(port);
    return 0;
#endif
}

/*!
 * @brief   Clears interrupt.
 *
 * @param   port        Port of PORT.
 * @param   pinIndex    Number of GPIO input pin which asserted interrupt.
 */
static inline void GPIO_AML_ClearInterruptFlags(aml_port_t port, uint8_t pinIndex)
{
#if (SDK_VERSION == KINETIS_SDK_2_0 || SDK_VERSION == S32K1_SDK_3_0_0)
    g_portBases[port]->ISFR = (uint32_t)(1U << pinIndex);
#elif (SDK_VERSION == S32K3_RTD_LLD ||SDK_VERSION == S32K3_RTD_MCAL)
    /* Please clear interrupt flags through RTD APIs when S32K3 RTD LLD and MCAL is used. */
    AML_UNUSED(port);
    AML_UNUSED(pinIndex);
#endif
}

/*!
 * @brief   Changes pin direction.
 *
 * @param   port        Port of PORT.
 * @param   pinIndex    Pin index in context of selected port.
 * @param   pinDir      Pin direction.
 */
static inline void GPIO_AML_SetDirection(aml_port_t port, uint8_t pinIndex, 
        gpio_aml_pin_direction_t pinDir)
{
#if (SDK_VERSION == KINETIS_SDK_2_0)
    gpio_pin_config_t gpioPinConfig = {
            ((pinDir == gpioDirDigitalInput) ? kGPIO_DigitalInput : kGPIO_DigitalOutput), 
            0U
    };
        
    GPIO_PinInit(g_gpioBases[port], pinIndex, &gpioPinConfig);
#elif (SDK_VERSION == S32K1_SDK_3_0_0)
    uint32_t direction = PINS_DRV_GetPinsDirection(g_gpioBases[port]);

    direction &= ~(1U << pinIndex);
    direction |= (pinDir == gpioDirDigitalInput) ? (0U << pinIndex) : (1U << pinIndex);
    PINS_DRV_SetPinsDirection(g_gpioBases[port], direction);
#elif (SDK_VERSION == S32K3_RTD_LLD ||SDK_VERSION == S32K3_RTD_MCAL)
    /* Please configure pin direction through RTD APIs when S32K3 RTD LLD and MCAL is used. */
    AML_UNUSED(port);
    AML_UNUSED(pinIndex);
    AML_UNUSED(pinDir);
#endif
}
/*! @} */

#endif /* SOURCE_MIDDLEWARE_GPIO_H_ */

 /*******************************************************************************
 * EOF
 ******************************************************************************/
