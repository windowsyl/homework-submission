#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

typedef struct myprogress {
    double lastruntime;
    CURL *curl;
} myprogress;

typedef struct memory {
   struct memory *next;
   size_t size;
   char *response;
} chunk;

static int xferinfo(myprogress *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    myprogress *myp = p;
    CURL *curl = myp->curl;
    double curtime = 0;
    curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME_T, &curtime);
    if((curtime - myp->lastruntime) >= 3) //MINIMAL_PROGRESS_FUNCTIONALITY_INTERVAL
    {
        myp->lastruntime = curtime;
        fprintf(stderr, "TOTAL TIME: %" CURL_FORMAT_CURL_OFF_T ".%06ld\r\n", (long)(curtime / 1000000), (long)((int)curtime % 1000000));
    }
    //fprintf(stderr, "UP: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T "  DOWN: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T "\r\n", ulnow, ultotal, dlnow, dltotal);
    fprintf(stderr,"DOWN: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T "\r\n", dlnow, dltotal);
    return 0;
}

static size_t buffer(void *data, size_t size, size_t nmemb, void **userp)
{
    static chunk *mem = NULL;
    //I can't give this function the first llist buffer because I don't know how big it should be until this function is called
    //instead I give it a dummy pointer in userp that this will point to the head of the llist
    //on future calls, mem stores the last entry in the llist, so future calls will know where to build off of.

    size_t realsize = size * nmemb; //size = 1, nmemb = actual chunk size
    chunk *ptr = malloc(sizeof(chunk) + sizeof(char)*(realsize + 1));
    ptr->next = 0; //this is important to initilize because the last chunk won't have a next chunk to initilize it, so when trying to dereference it, a simple "is it null" check won't be enough
    //as noticed by testing and a heck ton of troubleshooting...

    if(!ptr) {
        fprintf(stderr, "Things are breaking (out of Memory)\n");
        return 0;
    }
    if (!mem) {
        *userp = ptr; //please please please tell me i'm doing this right.
    } else {
        mem->next = ptr;
    }

    ptr->size = realsize + 1;
    ptr->response = strndup(data, realsize);
    ptr->response[realsize] = '\0';
    
    mem = ptr; //so then the next time this is called, the buffer will be ready with the last element of the linked list so it can connect the new chunk
    return realsize;
}

/* initial was doing stuff with buffers so it would return a char *, but got some troubles with buffer size. current solve was going to just have a running
sum with a static in buffer that it would sneak out through the head, but  that sounded awful so here we are. (turns out it might have been a different issue i was misdiagnosing but won't try to do this rn)
void llDumpFree(chunk *head, char *buffer)
{   
    if(buffer){
        while (head && head != (void *)0xbebebebebebebebe) { //for some reason address sanitizer would try to dereference the one on the right but normal run wouldn't, no clue what's up
            if (head->response) { 
                strcat(buffer, head->response);
            }
            chunk *old = head;
            head = head->next;
            free(old->response);
            free(old);
        }
    } else {//if no buffer is given, will just free the llist
        while (head && head != (void *)0xbebebebebebebebe) { //for some reason address sanitizer would try to dereference the one on the right but normal run wouldn't, no clue what's up
            chunk *old = head;
            head = head->next;
            free(old->response);
            free(old);
        }
    }
}
*/

void llDumpFree(chunk *head)
{   
    if(head) {
        if(head->response) { 
            fprintf(stdout, "%s", head->response);
            free(head->response);
        }
        if(head->next) {
            llDumpFree(head->next);
        }
        free(head);
    }
}

chunk *download_url(const char *url) {
    CURL *curl = curl_easy_init();
    if(curl == NULL) {
        fprintf(stderr, "Things are breaking (couldn't init)\n");
    }
    myprogress progress;
    progress.lastruntime = 0;
    progress.curl = curl;
    CURLcode res = CURLE_OK;
    
    curl_easy_setopt(curl, CURLOPT_URL, url); //setopt will copy the url itself i think, no need for strcpy
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfo);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &progress);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    chunk *head;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &head);

    //curl_easy_setopt(curl, CURLOPT_HEADER, 1L); //trying to solve a prolem with LENGTH_DOWNLOAD

    res = curl_easy_perform(curl);

    /* (turns out this might have been other issues but it's finally working monday night so i'm not going to try to get it to work rn.)
    ****had a lot of trouble using CURLINFO_CONTENT_LENGTH_DOWNLOAD_T and would constantly overflow the buffer, my first guess was problems with the header
    ****but i couldn't get it to work after messing around with the function, so instead the user just has to deal with a llist head. 
    curl_off_t dltotal;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &dltotal); //it *liesss* ??? I assume it's a thing with header info but idk
    fprintf(stderr, "a birde told me you need %ld bytes\n", dltotal);
    dltotal = 6000000;
    char *output = malloc(sizeof(char)*(dltotal + 1));
    llDumpFree(head, output);  
    curl_easy_cleanup(curl);
    return output;
    */ 

   if(res != 0) {
        printf("Things are breaking (couldn't preform: res = %d)\n", res);
   }
   curl_easy_cleanup(curl);
   return head;
    
}

int main(int argc, char *argv[] ) {
    
    //chunk *output = download_url("https://google.com");
    chunk *output;
    if(argc > 1) {
        output = download_url(argv[1]);    
    } else {
        fprintf(stderr, "using 'big-sequence'\n");
        output = download_url("https://misterfifths.github.io/file-dump/curl/big-sequence");
    }
    llDumpFree(output);
    return 0;
}