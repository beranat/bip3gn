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
* syscall.c - LibC Syscall Loopbacks
***************************************************************************/
#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

int _close(int) {
	errno = EPERM;
	return -1;
}

off_t _lseek(int, off_t, int) {
	errno = EPERM;
	return (off_t)-1;
}

ssize_t _read(int, void *, size_t) {
	errno = EPERM;
	return -1;
}

ssize_t _write(int, const void *, size_t) {
	errno = EPERM;
	return -1;
}
