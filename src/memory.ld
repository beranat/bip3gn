/* vim: tabstop=2 shiftwidth=2 noexpandtab colorcolumn=76:
****************************************************************************
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
* memory.ld - Memory Layout for STM32G030
***************************************************************************/
MEMORY {
	RAM(w): ORIGIN = 0x20000000, LENGTH = 8K
	FLASH(rx): ORIGIN = 0x8000000, LENGTH = 32K
}
