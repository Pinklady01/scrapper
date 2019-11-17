#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curl/curl.h"
#include "conf_funcs.h"
#include "scrap_funcs.h"
#include "parser/parser.h"

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

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
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

    curl_global_cleanup();
    return 0;
}


void scrap(action * a,task* t) {
    int isVersioning = 0;
    createDirectoryFromPath("",a);

    char pageName[100];
    sprintf(pageName, "../%s/%s.html",a->name,a->name);
    FILE *f = fopen(pageName, "wb");

    char* path = malloc(sizeof(char) * (strlen(a->name) + 8));
    strcpy(path ,"Targets/");
    //strcat(path,a->name);
    //printf("%s\n",path);
    createDirectoryIfNotExist(path,a);

    printf("scrap start for %s\n\n", a->url);

    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, a->url);

#ifdef SKIP_PEER_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);


        for (int i = 0; i < a->nbOptions; i++) {
            if (strcmp(a->options[i]->key, "max-depth") == 0) {
                if (0 < atoi(a->options[i]->value)) {
                    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, (long) atoi(a->options[i]->value) + 1);
                }
            } else if (strcmp(a->options[i]->key, "versioning") == 0) {
                if (isVersioningOn(a->options[i]->value) == 1) {
                    isVersioning = 1;
                }
            }

        }

        if (f) {
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);

            res = curl_easy_perform(curl);

            if (res) {
                printf("ERROR : \n %s\n", curl_easy_strerror(res));
            }
            fclose(f);
        }
        f = fopen(pageName, "rb");
        int sizeFile = calculateFileSize(pageName);
        char *contentFile = malloc(sizeFile);
        int nb = fread(contentFile, 1, sizeFile, f);
        if (nb != sizeFile) {
            if (ferror(f)) {
                perror("ERREUR ");
            }

        }
        fillFileFromHTML(contentFile,a);
        saveAction(isVersioning, path,t->name);
        fclose(f);
        printf("file close\n");
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        printf("curl clear\n");
    }
}

void saveAction(int isVersioning, char* path, char* tacheName)
{
    if(isVersioning == 1)
    {
        char* fullPath = malloc(sizeof(char)*(strlen(path)+15));
        strcpy(fullPath,path);
        strcat(fullPath,"/versioning.txt");

        char buffer[256];
        time_t timestamp = time(NULL);

        strftime(buffer, sizeof(buffer), "%A %d %B %Y - %X.", localtime(&timestamp));
        printf("%s\n", buffer);

        writeFile(buffer,fullPath);
        writeFile("\n",fullPath);
        writeFile(tacheName,fullPath);
        writeFile("\n",fullPath);
        writeFile("---------------------",fullPath);
        free(fullPath);
    }
    printf("end\n");
}

int isVersioningOn(char* value)
{
    for(int i = 0; i < strlen(value);i++)
    {
        if(value[i] == 'o' && i < strlen(value)-1)
        {
            if(value[i+1] == 'n')
            {
                if(i-1 < 0 && i+2 == strlen(value))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
