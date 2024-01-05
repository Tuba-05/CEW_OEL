#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

// Callback function to write data received from the API
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to make an HTTP request and save the JSON data to a file
void makeHttpRequest(const char *url, const char *filename) {
    CURL *curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a CURL handle
    curl = curl_easy_init();
    if (curl) {
        // Set the API URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set the callback function to handle the received data
        struct MemoryStruct chunk;
        chunk.memory = malloc(1);
        chunk.size = 0;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Save JSON data to a file
            FILE *json_file = fopen(filename, "w");
            fprintf(json_file, "%s", chunk.memory);
            fclose(json_file);
        }

        // Cleanup libcurl
        curl_easy_cleanup(curl);
        free(chunk.memory);
    }

    // Cleanup libcurl
    curl_global_cleanup();
}
void parseJsonAndAppendToFile(const char *jsonFilename, const char *outputFilename) {
    // Load JSON data from file
    FILE *file = fopen(jsonFilename, "r");
    if (!file) {
        fprintf(stderr, "Error opening JSON file\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *json_data = (char *)malloc(file_size + 1);
    if (!json_data) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return;
    }

    fread(json_data, 1, file_size, file);
    fclose(file);
    json_data[file_size] = '\0';

    // Parse JSON data
    json_object *root_obj = json_tokener_parse(json_data);
    if (!root_obj) {
        fprintf(stderr, "Error parsing JSON data\n");
        free(json_data);
        return;
    }

    // Extract values
    json_object *components_obj, *timestamp_obj;
    if (json_object_object_get_ex(root_obj, "list", &components_obj) &&
        json_object_array_length(components_obj) > 0) {
        
        json_object *first_item = json_object_array_get_idx(components_obj, 0);
        if (first_item && json_object_object_get_ex(first_item, "components", &components_obj) &&
            json_object_object_get_ex(first_item, "dt", &timestamp_obj)) {

            double co, no, so2;
            json_object *co_obj, *no_obj ,*so2_obj;
            if (json_object_object_get_ex(components_obj, "co", &co_obj) &&
                json_object_object_get_ex(components_obj, "no", &no_obj) &&
                json_object_object_get_ex(components_obj, "so2", &so2_obj)) {
                co = json_object_get_double(co_obj);
                no = json_object_get_double(no_obj);
                so2 = json_object_get_double(so2_obj);

                long timestamp = json_object_get_int64(timestamp_obj);

                // Open the output file in append mode
                FILE *output_file = fopen(outputFilename, "a");
                if (!output_file) {
                    fprintf(stderr, "Error opening output file\n");
                    free(json_data);
                    json_object_put(root_obj);
                    return;
                }
                // Format timestamp as YYYY-MM-DD HH:MM:SS
                char timestamp_str[20];
                strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));

                // Append values to text file with the desired format
                fprintf(output_file, "Timestamp: %s\n", timestamp_str);
                fprintf(output_file, "CO=%.2f\n", co);
                fprintf(output_file, "NO=%.2f\n", no);
                fprintf(output_file, "SO2=%.2f\n", so2);

                fclose(output_file);
            } else {
                fprintf(stderr, "Error extracting values from JSON data\n");
            }
        } else {
            fprintf(stderr, "Error accessing array elements or components in JSON data\n");
        }
    } else {
        fprintf(stderr, "Error accessing 'list' array or array is empty in JSON data\n");
    }

    // Cleanup
    free(json_data);
    json_object_put(root_obj);
}



int main(void) {
    // Make HTTP request and save JSON data to a file
    makeHttpRequest("https://api.openweathermap.org/data/2.5/air_pollution?lat=31.5204&lon=74.3587&appid=df519bb5448393151ea2a53ff404e39d", "air_pollution_data.json");

    // Parse JSON data and append values to a text file
    parseJsonAndAppendToFile("air_pollution_data.json", "output.txt");

    return 0;
}
