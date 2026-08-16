#pragma once
// Post-deep-sleep microphone fix: gpio_reset_pin alone does NOT free
// GPIO19/20 after a deep-sleep wake — the USB-Serial-JTAG function is a
// dedicated PAD connection, not a GPIO-matrix route, so the PHY itself must
// be disabled. Safe on this board: flashing and serial debug run through the
// external CH343P bridge on UART0, never the native USB-JTAG.
#include "soc/usb_serial_jtag_struct.h"
#include "driver/gpio.h"

static inline void release_usb_jtag_pins() {
  USB_SERIAL_JTAG.conf0.usb_pad_enable = 0;
  gpio_reset_pin(GPIO_NUM_19);
  gpio_reset_pin(GPIO_NUM_20);
}
