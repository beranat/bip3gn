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
* stm32_assert.h - STM32-HAL/LL Assertion
***************************************************************************/
#pragma once

#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr)?(void)0U:assert_failed(__FILE__, __LINE__))
void assert_failed(const char *file, int line);
#else
#define assert_param(expr) ((void)0U)
#endif
