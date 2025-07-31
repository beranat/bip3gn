// vim: tabstop=4 shiftwidth=4 noexpandtab colorcolumn=76:
/***************************************************************************
* Beeper Engine (bip3gn) Copyright (C) 2025 madRat
****************************************************************************
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3 of the License.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program.  If not, see <http://www.gnu.org/licenses/
****************************************************************************
* stm32g0xx_it.c - STM32G0xx Interrupt Handles Loopbacks
***************************************************************************/
#include <cmsis_compiler.h>

#include "stm32g0xx_it.h"
#include "hw.h"

static const char *defaultHandler = "IRQ";

void NMI_Handler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void HardFault_Handler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void SVC_Handler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void PendSV_Handler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void SysTick_Handler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void WWDG_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void RTC_TAMP_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void FLASH_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void RCC_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void I2C1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void I2C2_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void SPI1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void SPI2_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void USART1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void USART2_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void EXTI0_1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void EXTI2_3_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void EXTI4_15_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM1_CC_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM3_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM14_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM16_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void TIM17_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void ADC1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void DMA1_Channel1_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void DMA1_Channel2_3_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}

void DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler(void) {
	hwCritical(defaultHandler, __LINE__);
}
