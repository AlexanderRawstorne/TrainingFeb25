/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main,LOG_LEVEL_DBG);


int main(void)
{
	//LOG_INF("Hello World! %s", CONFIG_BOARD_TARGET);
	//LOG_INF("The board is %s",CONFIG_BOARD_TARGET);
	LOG_INF("%s %s",CONFIG_MY_MESSAGE,CONFIG_BOARD);
	//printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	return 0;
}
