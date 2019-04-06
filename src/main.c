 /*
 * Copyright (c) 2018, Piyush Itankar <pitankar@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "os.h"

void thread1 () {
	while (1){
		for (int i=0; i<1000000; i++);
    GPIO_PORT_F->DATA[pin_1] = pin_1;

		for (int i=0; i<1000000; i++);
    GPIO_PORT_F->DATA[pin_1] = ~pin_1;
	}
}

void thread2 () {
	while (1) {
		for (int i=0; i<10000000; i++);
    GPIO_PORT_F->DATA[pin_2] = pin_2;

		for (int i=0; i<10000000; i++);
    GPIO_PORT_F->DATA[pin_2] = ~pin_2;
	}
}

void thread3 () {
	while (1) {
		for (int i=0; i<10000; i++);
    GPIO_PORT_F->DATA[pin_3] = pin_3;

		for (int i=0; i<10000; i++);
    GPIO_PORT_F->DATA[pin_3] = ~pin_3;
	}
}

void setup_leds() {
  SYS_CTRL->RCGC2       |= clk_port_F;
  GPIO_PORT_F->GPIODIR   = pin_3|pin_2|pin_1;
  GPIO_PORT_F->GPIODEN   = pin_3|pin_2|pin_1;
}

int main( void ){
  setup_leds();
  system_init();

	create_thread(thread1);
  create_thread(thread2);
	create_thread(thread3);

  while(1)
    __asm("WFI");
}
