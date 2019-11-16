#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curl/curl.h"
#include "conf_funcs.h"
#include "scrap_funcs.h"

size_t getData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int getRessourcesStream(char *url,char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE* f=fopen(filename,"wb");


    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            fclose(f);
            curl_easy_cleanup(curl);
            return -1;
        }
        fclose(f);
        curl_easy_cleanup(curl);
    }
    return 0;
}

void scrap(action * a){
    char * pageFilename = malloc(sizeof(char) * (strlen(a->name) + 6));
    strcpy(pageFilename, a->name);
    strcat(pageFilename, ".html");

    FILE * f = fopen(pageFilename, "wb");

    printf("scrap start for %s\n\n", a->url);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL * curl = curl_easy_init();

    if (curl){
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, a->url);

#ifdef SKIP_PEER_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
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

    curl_global_cleanup();
    printf("\nscrap end\n\n\n\n");
}