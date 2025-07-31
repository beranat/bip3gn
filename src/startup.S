# vim: tabstop=2 shiftwidth=2 noexpandtab colorcolumn=76 :
#***************************************************************************
# Beeper Engine (bip3gn) Copyright (C) 2025 madRat
#***************************************************************************
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/
#***************************************************************************
# startup.S - Entry Point and Low Initialization Code
#***************************************************************************
.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb

.global g_pfnVectors
.global Reset_Handler

.extern NMI_Handler
.extern HardFault_Handler
.extern SVC_Handler
.extern PendSV_Handler
.extern SysTick_Handler
.extern WWDG_IRQHandler                   /* Window WatchDog */
.extern RTC_TAMP_IRQHandler               /* RTC through the EXTI line */
.extern FLASH_IRQHandler                  /* FLASH */
.extern RCC_IRQHandler                    /* RCC */
.extern EXTI0_1_IRQHandler                /* EXTI Line 0 and 1 */
.extern EXTI2_3_IRQHandler                /* EXTI Line 2 and 3 */
.extern EXTI4_15_IRQHandler               /* EXTI Line 4 to 15 */
.extern DMA1_Channel1_IRQHandler          /* DMA1 Channel 1 */
.extern DMA1_Channel2_3_IRQHandler        /* DMA1 Channel 2,3 */
.extern DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler /* DMA1 Ch 4,5 DMAMUX1 overrun */
.extern ADC1_IRQHandler                   /* ADC1 */
.extern TIM1_BRK_UP_TRG_COM_IRQHandler    /* TIM1 Break, Update, Trigger and Commutation */
.extern TIM1_CC_IRQHandler                /* TIM1 Capture Compare */
.extern TIM3_IRQHandler                   /* TIM3 */
.extern TIM14_IRQHandler                  /* TIM14 */
.extern TIM16_IRQHandler                  /* TIM16 */
.extern TIM17_IRQHandler                  /* TIM17 */
.extern I2C1_IRQHandler                   /* I2C1 */
.extern I2C2_IRQHandler                   /* I2C2 */
.extern SPI1_IRQHandler                   /* SPI1 */
.extern SPI2_IRQHandler                   /* SPI2 */
.extern USART1_IRQHandler                 /* USART1 */
.extern USART2_IRQHandler                 /* USART2 */

// Initializaed data
.word _sidata
.word _sdata
.word _edata

// BSS-data
.word _sbss
.word _ebss

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word 0
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  .word WWDG_IRQHandler
  .word 0
  .word RTC_TAMP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_1_IRQHandler
  .word EXTI2_3_IRQHandler
  .word EXTI4_15_IRQHandler
  .word 0
  .word DMA1_Channel1_IRQHandler
  .word DMA1_Channel2_3_IRQHandler
  .word DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler
  .word ADC1_IRQHandler
  .word TIM1_BRK_UP_TRG_COM_IRQHandler
  .word TIM1_CC_IRQHandler
  .word 0
  .word TIM3_IRQHandler
  .word 0
  .word 0
  .word TIM14_IRQHandler
  .word 0
  .word TIM16_IRQHandler
  .word TIM17_IRQHandler
  .word I2C1_IRQHandler
  .word I2C2_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word 0

.section .text.Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0

  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss
  bl __libc_init_array
  bl main

LoopForever:
  b LoopForever

.size Reset_Handler, .-Reset_Handler
