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
* hw.c - Hardware Specific and Initialization Code Implementation
***************************************************************************/
#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>

#include <system_stm32g0xx.h>

#include <stm32g0xx_ll_cortex.h>
#include <stm32g0xx_ll_rcc.h>
#include <stm32g0xx_ll_bus.h>
#include <stm32g0xx_ll_system.h>
#include <stm32g0xx_ll_utils.h>
#include <stm32g0xx_ll_gpio.h>

#include "hw.h"

#if (HSI_VALUE != 16000000UL)
	#error("Invalid or redefined HSI oscillator")
#endif

#if (LSI_VALUE != 32000UL)
	#error("Invalid or redefined LSI oscillator")
#endif

uint32_t SystemCoreClock = HSI_VALUE;

const uint32_t AHBPrescTable[16UL] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL,
									  1UL, 2UL, 3UL, 4UL, 6UL, 7UL, 8UL, 9UL};
const uint32_t APBPrescTable[8UL] = {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

static void delay(uint32_t ticks) {
	while (ticks > 0U) {
		if (0U != LL_SYSTICK_IsActiveCounterFlag())
			--ticks;
	}
}

static void configureClocks(void) {
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2);

	LL_RCC_HSI_Enable();
	while (0U == LL_RCC_HSI_IsReady());

	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_Enable();
	LL_RCC_PLL_EnableDomain_SYS();
	while(LL_RCC_PLL_IsReady() != 1);

	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
}

void hwInit(void) {
	__disable_irq();

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	configureClocks();
	SystemCoreClockUpdate();
	assert(SystemCoreClock == 64000000);
	LL_SetSystemCoreClock(SystemCoreClock);

	// Init SysTick 1ms
	LL_Init1msTick(SystemCoreClock);
}

void SystemCoreClockUpdate(void) {
	uint32_t tmp;
	uint32_t pllvco;
	uint32_t pllr;
	uint32_t pllsource;
	uint32_t pllm;
	uint32_t hsidiv;

	/* Get SYSCLK source
	 * -------------------------------------------------------*/
	switch (RCC->CFGR & RCC_CFGR_SWS) {
		case RCC_CFGR_SWS_0: /* HSE used as system clock */
			SystemCoreClock = HSE_VALUE;
			break;

		case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0): /* LSI used as system clock */
			SystemCoreClock = LSI_VALUE;
			break;

		case RCC_CFGR_SWS_2: /* LSE used as system clock */
			SystemCoreClock = LSE_VALUE;
			break;

		case RCC_CFGR_SWS_1: /* PLL used as system clock */
			pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC);
			pllm = ((RCC->PLLCFGR & RCC_PLLCFGR_PLLM) >> RCC_PLLCFGR_PLLM_Pos) +
				   1UL;
			pllvco =
				(pllsource == 0x03UL) ? (HSE_VALUE / pllm) : (HSI_VALUE / pllm);
			pllvco = pllvco * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >>
							   RCC_PLLCFGR_PLLN_Pos);
			pllr =
				(((RCC->PLLCFGR & RCC_PLLCFGR_PLLR) >> RCC_PLLCFGR_PLLR_Pos) +
				 1UL);
			SystemCoreClock = pllvco / pllr;
			break;

		case 0x00000000U: /* HSI used as system clock */
		default:		  /* HSI used as system clock */
			hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV)) >>
							  RCC_CR_HSIDIV_Pos));
			SystemCoreClock = (HSI_VALUE / hsidiv);
			break;
	}

	tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
	SystemCoreClock >>= tmp;
}

void hwCritical(const char *name, int id) {
#ifdef DEBUG
	__asm volatile("bkpt 0");
#endif
	__disable_irq();

	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOC);
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOD);
#ifdef LL_IOP_GRP1_PERIPH_GPIOE
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOE);
#endif
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOF);
#ifdef LL_IOP_GRP1_PERIPH_GPIOG
	LL_IOP_GRP1_DisableClock(LL_IOP_GRP1_PERIPH_GPIOG);
#endif

	while(true);
}

__NO_RETURN void __assert_func(const char *file, int line, const char *af, const char *exp) {
	hwCritical("Gcc-Assert", line);
}

#ifdef USE_FULL_ASSERT
void assert_failed(const char *file, uint32_t line) {
	hwCritical("Assert", (int)line);
}
#endif //#ifdef USE_FULL_ASSERT
