#include "network.h"

int main(void) {
    int request;
    int response;
    socketif_t socket;
    char hostAddress[MAXADDRESSLEN];
    int clientPort;
    int localport = 35000;
    int cont = 0; // richieste soddisfatte

    socket = createUDPInterface(localport);
        
    do{
        printf("[SERVER] Sono in attesa di richieste da qualche client\n");

        UDPReceive(socket, &request, sizeof(request), hostAddress, &clientPort);

        printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, clientPort);
            
        printf("[SERVER] Contenuto: %d\n", request);
            
        response += request;
    }while(request != 0);

    UDPSend(socket, &response, sizeof(response), hostAddress, clientPort);


    do {
        UDPReceive ( socket , &request , sizeof (request) , hostAddress , &clientPort ) ;
        UDPSend ( socket , &response, sizeof ( response ) , hostAddress , clientPort ) ;
    } while ( true );
}

