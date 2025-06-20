#include "network.h"
#include <stdio.h>
#include <string.h>

int main(){
    connection_t connection;
    char request[40];
    FILE *file;
    int fd;
    char character = 'a';
    
    connection = createTCPConnection("localhost", 35000);
    

    printf("[CLIENT] Inserisci il nome di un file:\n");
    scanf("%s", &request);

    printf("[CLIENT] Invio richiesta con nome file al server\n");
    TCPSend(connection, &request, sizeof(request));

    file = fopen("/home/Dimitri/testo.txt", "w");
    if (file == NULL){
        printf("Errore apertura file %s \n", "/home/Dimitri/testo.txt");
        exit(0);
    }

   while (TCPReceive(connection, &character, sizeof(character)) > 0) {
        fputc(character, file);
    }

    printf("[CLIENT] Ho ricevuto il file dal server.\n");
    printf("[CLIENT] Chiudo la connessione.\n");
    
    closeConnection(connection);
    fclose(file);
}

