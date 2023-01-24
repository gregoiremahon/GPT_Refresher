//
//  main.c
//  GPT_Refresher
//
//  Created by Grégoire Mahon on 24/01/2023.
//

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    CURL *curl;
    const char* url = "https://chat.openai.com/chat";
    CURLcode res;
    char *page_content = NULL;
    int found = 0;
    printf("Trying to refresh the page : %s\n", url);
    while (!found) {
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &page_content);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);
        }

        if (page_content != NULL) {
            found = strstr(page_content, "login") != NULL;
            free(page_content);
            page_content = NULL;
        }

        if (!found) {
            printf("Login not found, refreshing...\n");
            sleep(1);
        }
    }
    // if "login" is found on chatGPT page, that means you can access to it, log in and use GPT
    printf("Login found\nVisit%s\n", url);

    return 0;
}
