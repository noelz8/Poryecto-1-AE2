#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <ImageProcessing.hpp>
#include <cmath>

using namespace cv;
using namespace std;


int main()
{

    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Cant create a socket";
        return -1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

       bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Esuchando para una posible conexion
    listen(listening, SOMAXCONN);
 
    // Esperando una conexion
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      
    char service[NI_MAXSERV];   
 
    memset(host, 0, NI_MAXHOST); 
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Se cierra el socket en escucha
    close(listening);
 
    char buf[4096];
    char buf2[4096];
    char fact[4096];
    
    char *path;
    while (true)
    {
        memset(buf, 0, 4096);
        memset(buf2, 0, 4096);
        memset(fact, 0, 4096);
    
        char *err = "No se pudo encontrar la imagen\n";
        // Esperando a que el cliente envie el mensaje
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recv(). Quitting" << endl;
            break;
        }
 
        if (bytesReceived == 0)
        {
            cout << "Client disconnected " << endl;
            break;
        }

        ImageProcessing image;
        image.read(buf);
        if(image.image.empty()){
            send(clientSocket, err, strlen(err)+1,0);
            cout << "Imagen no encontrada\n";
            break;
        }
        char *men = "Eliga el filtro a aplicar\n 1: Gaussian Blur\n 2: Escala de grises\n 3: Control de brillo\n 4: Correccion de gama\n";
        char *factor = "Indique el factor de brillo que desea aplicar: \n";
        char *gamma = "Indique el gamma a utilizar\n";
        path = buf;
  
       
        
        send(clientSocket, men, strlen(men) + 1, 0);

        int bytes2 = recv(clientSocket, buf2, 4096, 0);

        if (bytes2 == -1){
            
            cerr << "Error al recibir" << endl;
            break;
        }

        if (bytes2 == 0){
            
            cout << "Cliente desconectado " << endl;
            
        }

        if(string(buf2, 0, bytes2)=="1"){

            image.gaussianBlur();
            break;
        }

        if(string(buf2, 0, bytes2)=="2"){

            image.gray_scale();
            break;
        }

        if(string(buf2, 0, bytes2)=="3"){

            send(clientSocket, factor, strlen(factor)+1, 0);
            int facts = recv(clientSocket, fact, 4096, 0);
            image.brightControl(stoi(fact));
            break;
            


        }

        if (string(buf2, 0, bytes2)=="4"){

            send(clientSocket, gamma, strlen(gamma)+1, 0);
            int facts = recv(clientSocket, fact, 4096, 0);
            image.gammaCorrection(stoi(fact));
            break;
        }
   
    }
 
    // Close the socket
    close(clientSocket);
 

    return 0;
}
