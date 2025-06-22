#include "network.h"

int main(){
    char *HTMLResponse = "HTTP/1.1 200 OK\r\n\r\n<html><head><title>An Example Page</title></head><body>Hello World, this is a very simple HTML document.</body></html>\r\n";
    socketif_t sockfd;
    FILE* connfd, *file;
    int res, i;
    long length=0;
    char request[MTU], method[10], c;
    char boundary[MTU];
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        printf("%s", request);
        strcpy(method,strtok(request," "));
        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            printf("%s", request);
            if(strstr(request, "boundary=") != NULL) {
                char *boundary_start = strstr(request, "boundary=") + strlen("boundary=");
                strcpy(boundary, strtok(boundary_start, "\r\n"));
            }

            if(strstr(request, "Content-Length:")!= NULL)  {
                length = atol(request+15);
            }
        }


        if(strcmp(method, "POST")==0)  {
            char request[MTU];
            fread(request, 1, length, connfd);
            request[length] = '\0';

            char *filename = NULL;
            char *token = NULL;
            token = malloc(strlen(request));

            strcpy(token, request);

            strtok(token, "\"");
            strtok(NULL, "\"");
            strtok(NULL, "\"");  
            filename = strtok(NULL, "\"");
            free(token);


            char *start = strstr(request, "Content-Type:") + strlen("Content-Type:");
            start = strstr(start, "\r\n\r\n") + 4;
            char *end = strstr(start, boundary);
            end -= 4; // rimuove i carattrei \r\n\r\n--
            int len = end - start;
            char contenuto[len + 1];
            strncpy(contenuto, start, len);
            contenuto[len] = '\0';

            file = fopen(filename, "a+");
            fputs(contenuto, file);
            fclose(file);
        }
        
        fputs(HTMLResponse, connfd);
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}

