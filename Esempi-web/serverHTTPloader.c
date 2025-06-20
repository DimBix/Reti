#include "network.h"

int main(){
    socketif_t sockfd;
    FILE* connfd;
    int res, i;
    long length=0;
    char request[MTU], method[10], c;
    char filename[50];
    
    sockfd = createTCPServer(8000);
    if (sockfd < 0){
        printf("[SERVER] Errore: %i\n", sockfd);
        return -1;
    }
    
    while(true) {
        connfd = acceptConnectionFD(sockfd);
        
        fgets(request, sizeof(request), connfd);
        printf("%s", request);
        strcpy(method, strtok(request," "));
        strcpy(filename, strtok(NULL, " "));
        strtok(filename, "=");
        strcpy(filename, strtok(NULL, "="));

        while(request[0]!='\r') {
            fgets(request, sizeof(request), connfd);
            printf("%s", request);
            if(strstr(request, "Content-Length:")!=NULL)  {
                length = atol(request+15);
            }
        }
        
        FILE *file = fopen(filename, "r");

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
   
        const char* httpHeader = "HTTP/1.1 200 OK\r\n\r\n";
        size_t headerSize = strlen(httpHeader);
    
        char* contenuto = (char*)malloc(headerSize + fileSize + 1);

        strcpy(contenuto, httpHeader);
        fread(contenuto + headerSize, 1, fileSize, file);
        contenuto[headerSize + fileSize] = '\0';

        fputs(contenuto, connfd);
        fclose(file);
        fclose(connfd);
                
        printf("\n\n[SERVER] sessione HTTP completata\n\n");
    }
    
    closeConnection(sockfd);
    return 0;
}

