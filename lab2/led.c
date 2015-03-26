#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "mraa/gpio.h"

int main(int argc, char **argv)
{
mraa_platform_t platform = mraa_get_platform_type();
mraa_gpio_context gpio;
char board_name[] = "Some weird devboard that isn't recognised...";
int ledstate = 0;

switch (platform) {
case MRAA_INTEL_GALILEO_GEN1:
strcpy(board_name, "Intel Galileo Gen1");
gpio = mraa_gpio_init_raw(3);
break;
case MRAA_INTEL_GALILEO_GEN2:
strcpy(board_name, "Intel Galileo Gen2");
gpio = mraa_gpio_init(13);
break ;
default:
gpio = mraa_gpio_init(13);
}

fprintf(stdout, "Welcome to libmraa\n Version: %s\n Running on %s\n",
mraa_get_version(), board_name);

mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
for (;;) {
ledstate = !ledstate;
mraa_gpio_write(gpio, !ledstate);
sleep(1);
}

return 0;
}