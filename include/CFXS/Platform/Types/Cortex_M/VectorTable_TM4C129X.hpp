// ---------------------------------------------------------------------
// CFXS Framework Base Module <https://github.com/CFXS/CFXS-Base>
// Copyright (C) 2022 | CFXS / Rihards Veips
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
// ---------------------------------------------------------------------
// [CFXS] //
#pragma once
#include <CFXS/Base/Types.hpp>

namespace CFXS::Cortex_M {

    template<auto INITIAL_SP, VoidFunction_t RESET, VoidFunction_t DEFAULT_HANDLER>
    struct VectorTable_TM4C129X {
        size_t __SP                               = (size_t)INITIAL_SP;
        VoidFunction_t __Reset                    = RESET;
        VoidFunction_t isr_NMI                    = DEFAULT_HANDLER;
        VoidFunction_t isr_HardFault              = DEFAULT_HANDLER;
        VoidFunction_t isr_MPU_Fault              = DEFAULT_HANDLER;
        VoidFunction_t isr_BusFault               = DEFAULT_HANDLER;
        VoidFunction_t isr_UsageFault             = DEFAULT_HANDLER;
        VoidFunction_t __reserved0                = nullptr;
        VoidFunction_t __reserved1                = nullptr;
        VoidFunction_t __reserved2                = nullptr;
        VoidFunction_t __reserved3                = nullptr;
        VoidFunction_t isr_SVCall                 = DEFAULT_HANDLER;
        VoidFunction_t isr_DebugMonitor           = DEFAULT_HANDLER;
        VoidFunction_t __reserved4                = nullptr;
        VoidFunction_t isr_PendSV                 = DEFAULT_HANDLER;
        VoidFunction_t isr_SysTick                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_A                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_B                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_C                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_D                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_E                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_0                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_1                 = DEFAULT_HANDLER;
        VoidFunction_t isr_SPI_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_PWM_Fault              = DEFAULT_HANDLER;
        VoidFunction_t isr_PWM_Generator_0        = DEFAULT_HANDLER;
        VoidFunction_t isr_PWM_Generator_1        = DEFAULT_HANDLER;
        VoidFunction_t isr_PWM_Generator_2        = DEFAULT_HANDLER;
        VoidFunction_t isr_QuadratureEncoder_0    = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_0_Sequence_0       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_0_Sequence_1       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_0_Sequence_2       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_0_Sequence_3       = DEFAULT_HANDLER;
        VoidFunction_t isr_WatchdogTimer          = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_0A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_0B               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_1A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_1B               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_2A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_2B               = DEFAULT_HANDLER;
        VoidFunction_t isr_AnalogComparator_0     = DEFAULT_HANDLER;
        VoidFunction_t isr_AnalogComparator_1     = DEFAULT_HANDLER;
        VoidFunction_t isr_AnalogComparator_2     = DEFAULT_HANDLER;
        VoidFunction_t isr_SystemControl          = DEFAULT_HANDLER;
        VoidFunction_t isr_FlashControl           = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_F                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_G                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_H                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_2                 = DEFAULT_HANDLER;
        VoidFunction_t isr_SPI_1                  = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_3A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_3B               = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_1                  = DEFAULT_HANDLER;
        VoidFunction_t isr_CAN_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_CAN_1                  = DEFAULT_HANDLER;
        VoidFunction_t isr_Ethernet               = DEFAULT_HANDLER;
        VoidFunction_t isr_Hibernate              = DEFAULT_HANDLER;
        VoidFunction_t isr_USB_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_PWM_Generator_3        = DEFAULT_HANDLER;
        VoidFunction_t isr_DMA_SoftwareTransfer   = DEFAULT_HANDLER;
        VoidFunction_t isr_DMA_Error              = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_1_Sequence_0       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_1_Sequence_1       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_1_Sequence_2       = DEFAULT_HANDLER;
        VoidFunction_t isr_ADC_1_Sequence_3       = DEFAULT_HANDLER;
        VoidFunction_t isr_ExternalBusInterface_0 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_J                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_K                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_L                 = DEFAULT_HANDLER;
        VoidFunction_t isr_SPI_2                  = DEFAULT_HANDLER;
        VoidFunction_t isr_SPI_3                  = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_3                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_4                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_5                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_6                 = DEFAULT_HANDLER;
        VoidFunction_t isr_UART_7                 = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_2                  = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_3                  = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_4A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_4B               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_5A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_5B               = DEFAULT_HANDLER;
        VoidFunction_t isr_FPU                    = DEFAULT_HANDLER;
        VoidFunction_t __reserved_5               = nullptr;
        VoidFunction_t __reserved_6               = nullptr;
        VoidFunction_t isr_I2C_4                  = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_5                  = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_M                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_N                 = DEFAULT_HANDLER;
        VoidFunction_t __reserved_7               = nullptr;
        VoidFunction_t isr_Tamper                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P0                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P1                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P2                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P3                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P4                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P5                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P6                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_P7                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q0                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q1                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q2                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q3                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q4                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q5                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q6                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_Q7                = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_R                 = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_S                 = DEFAULT_HANDLER;
        VoidFunction_t isr_SHA_MD5_0              = DEFAULT_HANDLER;
        VoidFunction_t isr_AES_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_DES3DES_0              = DEFAULT_HANDLER;
        VoidFunction_t isr_LCD_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_6A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_6B               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_7A               = DEFAULT_HANDLER;
        VoidFunction_t isr_Timer_7B               = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_6                  = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_7                  = DEFAULT_HANDLER;
        VoidFunction_t isr_ScanMatrixKeyboard_0   = DEFAULT_HANDLER;
        VoidFunction_t isr_OneWire_0              = DEFAULT_HANDLER;
        VoidFunction_t isr_PS2_0                  = DEFAULT_HANDLER;
        VoidFunction_t isr_LED_Sequencer_0        = DEFAULT_HANDLER;
        VoidFunction_t isr_ConsumerIR_0           = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_8                  = DEFAULT_HANDLER;
        VoidFunction_t isr_I2C_9                  = DEFAULT_HANDLER;
        VoidFunction_t isr_GPIO_T                 = DEFAULT_HANDLER;
    };

} // namespace CFXS::Cortex_M