// clang -g -Wall -std=c11 curl.c -o curl -lcurl
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

typedef size_t (* recieve_data)(char *, size_t, size_t, void *);

size_t get(char *buff, size_t itemsize, size_t nitems, void *ignore) {

    size_t bytes = itemsize * nitems;
    printf("bulk size: %zu\n", bytes);
    return bytes;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "Please supply valid url\n");
        return EXIT_FAILURE;
    }
    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Init Failed\n");
        return EXIT_FAILURE;
    }

    // set options
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]); 
    /*
    "ftp://demo:password@test.rebex.net/readme.txt"
    "https://jacobsorber.com"
    */
    recieve_data get_data = get;
    // using callback function get_data into CURLOPT_WRITEFUNCTION
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_data);

    CURLcode result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        fprintf(stderr, "Download Failed With Err %s\n", curl_easy_strerror(result));
        return EXIT_FAILURE;
    }

    curl_easy_cleanup(curl);
    EXIT_SUCCESS;
}