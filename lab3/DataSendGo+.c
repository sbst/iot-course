#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

void dataSend(char *);

int main(int argc, char **argv)
{
        char* serveraddr = "168.63.82.20";
        char* did = "m89yilusa76q";

        FILE* temperature;
        char temp_string[7];
        double temp_number;
        char command_string[256];
        if(argv[1] == 0)
        {
                printf("Argument is lost\n");
                return 0;
        }
        int ix;
        for(ix = 0; ix < atoi(argv[1]); ++ix)
        {
                temperature = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
                fgets(temp_string, 7, temperature);

                temp_number = atof(temp_string) / 1000;
                sprintf(command_string,"http://%s/server/income/?did=%s&action=put&value=%f", serveraddr, did, temp_number);
                printf("%s", command_string);
                dataSend(command_string);
                fclose(temperature);
                sleep(5);
        }
        return 1;
}

                fgets(temp_string, 7, temperature);
                temp_number = atof(temp_string) / 1000;
                sprintf(command_string,



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
  return;
}	
	
