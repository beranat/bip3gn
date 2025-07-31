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
* main.c - 'main' and the Engine
***************************************************************************/
#include <stddef.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include <stm32g0xx_ll_bus.h>
#include <stm32g0xx_ll_rcc.h>
#include <stm32g0xx_ll_gpio.h>
#include <stm32g0xx_ll_tim.h>

#include "hw.h"

#define SPEAKER_PORT (GPIOB)
#define SPEAKER_PIN (LL_GPIO_PIN_5)
#define SPEAKER_GRP1_PERIPH (LL_IOP_GRP1_PERIPH_GPIOB)

//#define SPEAKER_PORT (GPIOA)
//#define SPEAKER_PIN (LL_GPIO_PIN_9)
//#define SPEAKER_GRP1_PERIPH (LL_IOP_GRP1_PERIPH_GPIOA)

// B5 - 987 HZ
#define B5 (4746U)

// A5 - 880 Hz
#define A5 (5352U)

// G5 - 784 Hz
#define G5 (6035U)

// F5 - 698 Hz
#define F5 (6810U)

// E5 - 659 Hz
#define E5 (7226U)

// D5 - 587 Hz
#define D5 (8140U)

// C5 - 523 Hz
#define C5 (9166U)

// B4 - 494 Hz
#define B4 (9718U)

// A4 - 440 Hz
#define A4 (10940U)

__attribute__((used)) static const uint32_t TONES[] = {
		0,   A4,
		0,   A4,
		0,   A4,
		0,   A4,
		0,   A4,
		0,     0,
	   B4,     0,
	   B4,     0,
	   B4,     0,
	   B4,     0,
	   B4,     0,
	    0,     0,
		0,    C5,
		0,    C5,
		0,    C5,
		0,    C5,
		0,    C5,
		0,     0,
	  D5,      0,
	  D5,      0,
	  D5,      0,
	  D5,      0,
	  D5,      0,
		0,     0,
	    0,     E5,
	    0,     E5,
	    0,     E5,
	    0,     E5,
	    0,     E5,
		0,     0,
	   F5,     0,
	   F5,     0,
	   F5,     0,
	   F5,     0,
	   F5,     0,
	    0,     0,
		0,    G5,
		0,    G5,
		0,    G5,
		0,    G5,
		0,    G5,
		0,     0,
	   A5,     0,
	   A5,     0,
	   A5,     0,
	   A5,     0,
	   A5,     0,
		0,     0,
	    0,     B5,
	    0,     B5,
	    0,     B5,
	    0,     B5,
	    0,     B5,
		0,     0,		0,     0,		0,     0,		0,     0,
		0,     0,		0,     0,		0,     0,		0,     0,
		0,     0,		0,     0,		0,     0,		0,     0,
		0,     0,		0,     0,		0,     0,		0,     0,
		0,     0,		0,     0,		0,     0,		0,     0,
		0,     0,		0,     0,		0,     0,		0,     0,
};

__attribute__((used)) static const size_t COUNT = sizeof(TONES)/sizeof(*TONES) / 2;

static void speakerInit(void) {
	LL_IOP_GRP1_EnableClock(SPEAKER_GRP1_PERIPH);

	LL_GPIO_InitTypeDef init = {
		.Pin = SPEAKER_PIN,
		.Mode = LL_GPIO_MODE_OUTPUT,
		.Pull = LL_GPIO_PULL_NO,
		.Speed = LL_GPIO_SPEED_FREQ_HIGH, // Balance between speed and quality
	};
	LL_GPIO_Init(SPEAKER_PORT, &init);
}

static __attribute__((used)) void speakerSetHigh(void) {
	WRITE_REG(SPEAKER_PORT->BSRR, SPEAKER_PIN);
}

static __attribute__((used)) void speakerSetLow(void) {
	WRITE_REG(SPEAKER_PORT->BRR, SPEAKER_PIN);
}

__attribute__((noreturn))  int main(void) {
	hwInit();

	speakerInit();

	__disable_irq();

	// R8 - COUNT
	// R7 - DELAY
	// R6 - TONES

	// R3 - FREQ0
	// R4 - FREQ1

	__asm volatile(
		".syntax UNIFIED                            ;"
		".cpu cortex-m0plus 						;"
		"    LDR R6, =TONES                         ;"
		"    LDR R0, =COUNT                         ;"
		"    LDR R0, [R0]                           ;"

		"_NEXT:                                      "
		"    MOV R8, R0                             ;"
		"    LDR R3, [R6]                           ;"
		"	 ADDS R6, R6, #4                        ;"
		"    LDR R4, [R6]                           ;"
		"	 ADDS R6, R6, #4                        ;"

		"	 MOV R1, R3                             ;"
		"	 MOV R2, R4                             ;"

		"    LDR R7, =#0x74000                     ;" // 100ms
		"_LOOP:                                      "

		// CHANNEL 0
		"    SUBS R1, R1, #1                        ;" // +1
		"    BNE _DONE0                             ;" // +2
		"	 MOV R1, R3                             ;" // +1
		"	 PUSH {R1-R3}                           ;" // +1 + 3
		"    CMP R3, #0                             ;" // +1
		"	 BEQ _SKIP0                             ;" // +2
		"    BL speakerSetHigh                      ;" // +3
		"_SKIP0:                                     "
		"    LDR R0, =#0x400                        ;"
		"_WAIT0:                                     "
		"    SUBS R0, R0, #1                        ;"
		"    BNE _WAIT0                             ;"
		"    BL speakerSetLow                       ;" // +3
		"	 POP {R1-R3}                            ;" // +4
		"_DONE0:                                     "

		// CHANNEL 1
		"    SUBS R2, R2, #1                        ;"
		"    BNE _DONE1                             ;"
		"	 MOV R2, R4                             ;"
		"	 PUSH {R1-R3}                           ;"
		"    CMP R4, #0                             ;"
		"	 BEQ _SKIP1                             ;"
		"    BL speakerSetHigh                      ;"
		"_SKIP1:                                     "
		"    LDR R0, =#0x400                        ;"
		"_WAIT1:                                     "
		"    SUBS R0, R0, #1                        ;"
		"    BNE _WAIT1                             ;"
		"    BL speakerSetLow                       ;"
		"	 POP {R1-R3}                            ;"
		"_DONE1:                                     "

		"    SUBS R7, R7, #1 				        ;" // +1
		"    BNE _LOOP 							    ;" // +2

		"    MOV R0, R8                             ;"
		"    SUBS R0, R0, #1 				        ;"
		"    BNE _NEXT                              ;"
		::: "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r8", "cc", "memory");

	NVIC_SystemReset();
	while (true);
}

