#include "mraa.hpp"

int main ()
{
uint16_t adc_value;
mraa::Aio* a0;

a0 = new mraa::Aio(0);
if (a0 == NULL) {
return MRAA_ERROR_UNSPECIFIED;
}

for(;;) {
adc_value = a0->read();
fprintf(stdout, "ADC A0 read %X - %d\n", adc_value, adc_value);
}

return MRAA_SUCCESS;
}