#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    string ubicacion, filtro, fact;
    

    //	Se crea el socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Se crea una estructura para unir el socket que estamos creando
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Se conecta al socket del server
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    char fekts[4096];
    


    do {
      
        cout << "Ingrese la ubicacion de la imagen: \r\n";
        getline(cin, ubicacion);
     

        //		Enviando mensajes al servidor
        int sendRes = send(sock, ubicacion.c_str(), ubicacion.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Esperando la respuesta del servidor
        memset(buf, 0, 4096);
        memset(fekts,0,4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "Ocurrio un error obteniendo la respuesta\r\n";
        }
        
            //		Mostrando la respuesta

        cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";

        cout << "> ";
        getline(cin, filtro);
        sendRes = send(sock, filtro.c_str(), filtro.size()+1, 0);   
       
        int factores = recv(sock, fekts, 4096, 0);

        cout << "SERVER> " << string(fekts, factores) << "\r\n"; 
    

        cout << "> ";
        getline(cin, fact);
        sendRes = send(sock, fact.c_str(), fact.size()+1, 0);


    } while(true);

    //	Close the socket
    close(sock);

    return 0;
}
