#include "network.h"

int main(void) {
    socketif_t socket;
    char response[]="Sono il server: ho ricevuto correttamente il tuo messaggio!\n";
    char request[MTU];
    char hostAddress[MAXADDRESSLEN];
    int clientPort;
    int localport = 100;
    int cont = 0; // richieste soddisfatte

    socket = createUDPInterface(localport);
    
    //true
    while(cont < 5) {
    
        printf("[SERVER] Sono in attesa di richieste da qualche client\n");
    
        UDPReceive(socket, request, MTU, hostAddress, &clientPort);
    
        printf("[SERVER] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, clientPort);
        printf("[SERVER] Contenuto: %s\n", request);
    
        UDPSend(socket, response, strlen(response), hostAddress, clientPort);
        cont++;
    }
    
}

