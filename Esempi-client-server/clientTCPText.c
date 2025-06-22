#include "network.h"
#include <stdio.h>
#include <string.h>

int main(){
    connection_t connection;
    char request[40];
    FILE *file;
    int fd;
    char character = 'a', *filename;
    
    connection = createTCPConnection("localhost", 35000);
    

    printf("[CLIENT] Inserisci il nome di un file:\n");
    scanf("%s", &request);

    printf("[CLIENT] Invio richiesta con nome file al server\n");
    TCPSend(connection, &request, sizeof(request));

    filename = strrchr(request, '/');
    filename++;

    file = fopen(filename, "a+");    
    if (file == NULL){
        printf("Errore apertura file %s \n", request);
        exit(0);
    }

    do{
        TCPReceive(connection, &character, sizeof(character));
        if(character < 0)
            break;
        fputc(character, file);
    }while(true);

    printf("[CLIENT] Ho ricevuto il file dal server.\n");
    printf("[CLIENT] Chiudo la connessione.\n");
    
    closeConnection(connection);
    fclose(file);
}

