#include "network.h"
#include <stdio.h>
#include <string.h>

int main(){
    connection_t connection;
    char receive[40];
    socketif_t server;
    FILE *file;
    char character;
    
    server = createTCPServer(35000);
    if (server < 0){
        printf("Error: %i\n", server);
        return -1;
    }
    
    connection = acceptConnection(server);
    printf("[SERVER] Connessione accettata.\n");
    printf("[SERVER] Attendo nome file dal client...\n");

    TCPReceive(connection, &receive, sizeof(receive) - 1);
    printf("[SERVER] Ho ricevuto il nome del file: %s\n", receive);


    file = fopen(receive, "r");
    if (file == NULL){
        printf("Errore apertura file %s \n", receive);
        exit(0);
    }


    do{
        character = fgetc(file);
        TCPSend(connection, &character, sizeof(character));
    }while(character > 0);

    printf("[SERVER] Ho inviato il file al client.\n");
    printf("[SERVER] Chiudo la connessione.\n");

    closeConnection(connection);
    fclose(file);
    
    return 0;
}

