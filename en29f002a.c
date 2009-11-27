/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2007 Carl-Daniel Hailfinger
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

/*
 * EN29F512 has 1C,21
 * EN29F010 has 1C,20
 * EN29F040A has 1C,04
 * EN29LV010 has 1C,6E and uses short F0 reset sequence
 * EN29LV040(A) has 1C,4F and uses short F0 reset sequence
 */

#include "flash.h"

int probe_en29f512(struct flashchip *flash)
{
	chipaddr bios = flash->virtual_memory;
	uint8_t id1, id2;

	chip_writeb(0xAA, bios + 0x555);
	chip_writeb(0x55, bios + 0x2AA);
	chip_writeb(0x90, bios + 0x555);

	programmer_delay(10);

	id1 = chip_readb(bios + 0x100);
	id2 = chip_readb(bios + 0x101);

	/* exit by writing F0 anywhere? or the code below */
	chip_writeb(0xAA, bios + 0x555);
	chip_writeb(0x55, bios + 0x2AA);
	chip_writeb(0xF0, bios + 0x555);

	printf_debug("%s: id1 0x%02x, id2 0x%02x\n", __func__, id1, id2);

	if (id1 == flash->manufacture_id && id2 == flash->model_id)
		return 1;

	return 0;
}

/*
 * EN29F002AT has 1C,92
 * EN29F002AB has 1C,97
 */

/* This does not seem to function properly for EN29F002NT. */
int probe_en29f002a(struct flashchip *flash)
{
	chipaddr bios = flash->virtual_memory;
	uint8_t id1, id2;

	chip_writeb(0xAA, bios + 0x555);
	chip_writeb(0x55, bios + 0xAAA);
	chip_writeb(0x90, bios + 0x555);

	programmer_delay(10);

	id1 = chip_readb(bios + 0x100);
	id2 = chip_readb(bios + 0x101);

	/* exit by writing F0 anywhere? or the code below */
	chip_writeb(0xAA, bios + 0x555);
	chip_writeb(0x55, bios + 0xAAA);
	chip_writeb(0xF0, bios + 0x555);

	printf_debug("%s: id1 0x%x, id2 0x%x\n", __func__, id1, id2);

	if (id1 == flash->manufacture_id && id2 == flash->model_id)
		return 1;

	return 0;
}
