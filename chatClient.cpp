/* Chat Program (Client)
*/

#include <iostream>
#include <signal.h>
#include <fstream>
#include <unistd.h>
#include <WINSOCK2.h>

using namespace std;

int main()
{
    //Initials
    WSADATA wsaData;
    WORD versionRequired=MAKEWORD(1,1);
    WSAStartup(versionRequired, &wsaData);

    SOCKET sockfd;
    SOCKADDR_IN sAddr;

    //1 - Establishing the connection
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    //2 - Server settings
    sAddr.sin_family=AF_INET;
    sAddr.sin_port=htons(9845);
    sAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");


    //4 - Listen to Connection
    char sMessage[1024],cMessage[1024];
    memset(cMessage,0,sizeof(cMessage));
    int result=connect(sockfd,(struct sockaddr*) &sAddr, sizeof(sAddr));

    cout<<"Waiting  for server..."<<endl;
    while(result==-1)
    {
        result=connect(sockfd,(struct sockaddr*) &sAddr, sizeof(sAddr)==-1);
        if(result==-1)
            sleep(1);
    }

    bool  cont=true;
    cout<<"Server connected!"<<endl;
    cout<<"-------------------------------------------"<<endl;
    while(cont)
    {
        cout<<"Enter message to Server: ";
        cin.get(cMessage,1024,'\n');
        cin.ignore(100,'\n');
        send(sockfd, cMessage, strlen(cMessage), 0);

        memset(sMessage,0,sizeof(sMessage));
        recv(sockfd, sMessage, sizeof(sMessage),0);
        cout<<"Server: "<<sMessage<<endl;

        if(!strcmp(sMessage,"Goodbye!"))
        {
            cont=false;
        }
    }

    closesocket(sockfd);
    WSACleanup();
}
