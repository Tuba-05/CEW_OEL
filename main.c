#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON/cJSON.h"
#include <time.h>
#include "air_quality.h"

// Helper function to read existing JSON array from a file
cJSON* readExistingArray() {
    FILE* file = fopen("output.json", "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char* fileContents = malloc(fileSize + 1);
        if (fileContents != NULL) {
            fread(fileContents, 1, fileSize, file);
            fclose(file);

            fileContents[fileSize] = '\0';

            // Parse existing JSON data
            cJSON* dataArray = cJSON_Parse(fileContents);
            free(fileContents);
            return dataArray;
        } else {
            fclose(file);
            fprintf(stderr, "Error allocating memory for file contents\n");
            return NULL;
        }
    }
    return NULL;
}

int main() {
    CURL* curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing libcurl\n");
        return 1;
    }

    const char* url = "http://api.openweathermap.org/data/2.5/air_pollution?lat=24.8607&lon=67.0011&appid=d485a877d60ae98bcc2131ef64c80858";
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    // Print the most recent data from output.txt, perform comparisons, save computed values, and check for anomalies
    // printMostRecentDataAndCompare();

    curl_easy_cleanup(curl);

    return 0;
}



