/*
 * Copyright (C) 2010 Michael Brown <mbrown@fensystems.co.uk>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * You can also choose to distribute this program under the terms of
 * the Unmodified Binary Distribution Licence (as given in the file
 * COPYING.UBDL), provided that you have satisfied its requirements.
 */

FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

/** @file
 *
 * Standard PC-BIOS reboot mechanism
 *
 */

#include <ipxe/reboot.h>
#include <realmode.h>
#include <bios.h>

/**
 * Reboot system
 *
 * @v warm		Perform a warm reboot
 */
static void bios_reboot ( int warm ) {
	uint16_t flag;

	/* Configure BIOS for cold/warm reboot */
	flag = ( warm ? BDA_REBOOT_WARM : 0 );
	put_real ( flag, BDA_SEG, BDA_REBOOT );

	/* Jump to system reset vector */
	__asm__ __volatile__ ( REAL_CODE ( "ljmp $0xf000, $0xfff0" ) );
}

PROVIDE_REBOOT ( pcbios, reboot, bios_reboot );
