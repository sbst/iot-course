#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mraa.hpp"

static int iopin = 13;
int running = 0;

void
sig_handler(int signo)
{
if (signo == SIGINT) {
printf("closing IO%d nicely\n", iopin);
running = -1;
}
}

int main (int argc, char **argv)
{
mraa_platform_t platform = mraa_get_platform_type();
switch (platform) {
case MRAA_INTEL_GALILEO_GEN1:
iopin = 3;
break;
case MRAA_INTEL_GALILEO_GEN2:
iopin = 13;
break ;
default:
iopin = 13;
}

if (argc < 2) {
printf("Provide an int arg if you want to flash an LED on some other IO port than IO %d\n", iopin);
} else {
iopin = strtol(argv[1], NULL, 10);
}

signal(SIGINT, sig_handler);

//! [Interesting]
mraa::Gpio* gpio = NULL;
switch (platform) {
case MRAA_INTEL_GALILEO_GEN1:
gpio = new mraa::Gpio(iopin,true,true);
break;
case MRAA_INTEL_GALILEO_GEN2:
gpio = new mraa::Gpio(iopin,true,false);
break;
default:
gpio = new mraa::Gpio(iopin,true,false);
}
if (gpio == NULL) {
return MRAA_ERROR_UNSPECIFIED;
}
int response = gpio->dir(mraa::DIR_OUT);
if (response != MRAA_SUCCESS)
mraa_result_print((mraa_result_t) MRAA_SUCCESS);

while (running == 0) {
response = gpio->write(1);
sleep(1);
response = gpio->write(0);
sleep(1);
}
delete gpio;
return response;
//! [Interesting]
}