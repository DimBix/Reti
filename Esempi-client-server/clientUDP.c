#include "network.h"

int main(void) {
    socketif_t socket;
    char request[]="Ciao sono il client!\n";
    char response[MTU];
    char hostAddress[MAXADDRESSLEN];
    int localPort = 30000;
    int serverPort = 100;
    
    socket = createUDPInterface(localPort);
    
    printf("[CLIENT] Spedisco messaggio al server\n");
    printf("[CLIENT] Contenuto: %s\n", request);
    UDPSend(socket, request, strlen(request), "127.0.0.1", serverPort);
     
    UDPReceive(socket, response, MTU, hostAddress, &serverPort);
    
    printf("[CLIENT] Ho ricevuto un messaggio da host/porta %s/%d\n", hostAddress, serverPort);
    printf("[CLIENT] Contenuto: %s\n", response);
}

