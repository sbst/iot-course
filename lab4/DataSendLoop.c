#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <curl/curl.h>
#include <mraa.hpp>

void dataSend(char *);
int dataGet();

int main(int argc, char **argv)
{
        char* serveraddr = "168.63.82.20";
        char* did = "m89yilusa76q";

        FILE* temperature;
        char temp_string[7];
        uint16_t temp_number;
        char command_string[256];
        int ix;
        while(true)
        {
                temperature =
fopen("/sys/class/thermal/thermal_zone0/temp", "r");
                fgets(temp_string, 7, temperature);

                temp_number = dataGet();
		sprintf(command_string,"http://%s/server/income/?did=%s&action=put&value=%d",serveraddr, did, temp_number);
                dataSend(command_string);
                fclose(temperature);
                sleep(1);
        }
        return 1;
}
int dataGet()
{
    int adc_value=0;
    mraa::Aio* a0;
    a0 = new mraa::Aio(0);
    if (a0 == NULL) {
        return 0;
    }
    adc_value = a0->read();
    return adc_value;
}

void dataSend(char* str)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, str);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
