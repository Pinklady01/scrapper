#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <curl/curl.h>
#include "conf_funcs.h"

size_t getData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

void scrap(action * a){
    char * pageFilename = malloc(sizeof(char) * (strlen(a->name) + 6));
    strcpy(pageFilename, a->name);
    strcat(pageFilename, ".html");

    FILE * f = fopen(pageFilename, "wb");

    printf("scrap start for %s\n\n", a->url);

    CURL * curl = curl_easy_init();

    if (curl){
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, a->url);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);

        for (int i = 0; i < a->nbOptions; i++){
            if (strcmp(a->options[i]->key, "max-depth") == 0){
                if ( 0 < atoi(a->options[i]->value) ){
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, (long) atoi(a->options[i]->value));
                }
            }
        }

        if (f){
            res = curl_easy_perform(curl);

            if (res) {
                printf("ERROR : \n %s\n", curl_easy_strerror(res));
            }

            /* close the header file */
            fclose(f);
        } else {
            printf("file error");
        }

        curl_easy_cleanup(curl);
    }

    printf("\nscrap end\n\n\n\n");
}