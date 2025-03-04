/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main,LOG_LEVEL_DBG);

#include <zephyr/display/cfb.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	//Display stuff
	struct device *display; 
	display = (struct device *) DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display)) {LOG_ERR("Display not Present");return (1);}

	if (cfb_framebuffer_init(display)) {LOG_ERR("Framebuffer initialization failed!\n");	return 1;}
	//cfb_framebuffer_invert(display);
	cfb_framebuffer_clear(display, true);


	cfb_framebuffer_set_font(display,0);
	cfb_print(display,"Hello",0,0);

	uint8_t x,y;
	cfb_get_font_size(display, 0, &x, &y);
	y--;
	cfb_framebuffer_set_font(display,1);
	cfb_print(display,"Line2",0,y);

	uint8_t off=y;
	cfb_get_font_size(display, 1, &x, &y);
	y--;
	cfb_framebuffer_set_font(display,2);
	cfb_print(display,"Line3",0,y+off);

	struct cfb_position st,en;

	st.x=80;
	st.y=0;
	en.x=128;
	en.y=64;
	cfb_draw_line(display,&st,&en);

	cfb_framebuffer_finalize(display);
    

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		//printf("LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
