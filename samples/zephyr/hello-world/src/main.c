/*
 * Copyright (c) 2017 Linaro, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "bootutil/bootutil_public.h"

#define SHARED_DATA_TLV_INFO_MAGIC    0x2016

#include <zephyr/devicetree.h>
#define RAM_BASE DT_REG_ADDR(DT_NODELABEL(sram0))
#define RAM_SIZE DT_REG_SIZE(DT_NODELABEL(sram0))
#define MCUBOOT_SHARED_DATA_SIZE     0x100
#define MCUBOOT_SHARED_DATA_BASE     (RAM_BASE + RAM_SIZE - MCUBOOT_SHARED_DATA_SIZE)

void printf_buf_hex(char *title, unsigned char *buf, int len ) {
    printf("\n%s(%d) : ", title, len);
    for (int i =0; i < len; i++) {
     if (i%1024==0) printf("\n");
     printf("%02X", (buf[i]&0xff));
    }
    printf("\n");
}

int main(void)
{
	printk("Hello World from %s on %s!\n",
	       MCUBOOT_HELLO_WORLD_FROM, CONFIG_BOARD);
	printk("Hello World from %s on %s!\n",
	       MCUBOOT_HELLO_WORLD_FROM, CONFIG_BOARD);
	printk("Hello World from %s on %s!\n",
	       MCUBOOT_HELLO_WORLD_FROM, CONFIG_BOARD);

	printf_buf_hex("boot record data", (uint8_t *)MCUBOOT_SHARED_DATA_BASE+8, *((uint16_t *)MCUBOOT_SHARED_DATA_BASE+3));

	boot_set_confirmed();

	return 0;
}
