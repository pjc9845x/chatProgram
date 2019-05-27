/* Chat Program (Server)
*/

#include <iostream>
#include <fstream>
#include <winsock.h>
using namespace std;


int main()
{
    //Initials
    WSADATA wsaData;
    WORD versionRequired=MAKEWORD(1,1);
    WSAStartup(versionRequired, &wsaData);

    SOCKET sockfd;
    SOCKADDR_IN sAddr, cAddr;

    //1 - Socket Initials
    int serverFd;

    //2 - Socket settings

    serverFd=socket(AF_INET,SOCK_STREAM,0);
    sAddr.sin_family=AF_INET;
    sAddr.sin_port=htons(9845);
    sAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    //3 - Bind
    bind(serverFd,(SOCKADDR*) &sAddr, sizeof(sAddr));

    //4 - Listen

    if(listen(serverFd,1)==-1)
    {
        cout<<"Error listening!"<<endl;
        return 0;
    }

    //5 - Begin
    char sMessage[1024],cMessage[1024];
    const char *welcome="Welcome!";
    memset(cMessage,0,sizeof(cMessage));

    int sLen=sizeof(sAddr);
    int cLen=sizeof(cAddr);

    cout<<"Waiting for connection..."<<endl;

    int clientFd=accept(serverFd, (struct sockaddr *)&cAddr, &cLen);
    if(clientFd==-1)
    {
        cout<<"Error accepting client"<<endl;
        return 0;
    }

    cout<<"Client connected!"<<endl;
    cout<<"-------------------------------------------"<<endl;
    bool cont=true;

    while(cont)
    {
        recv(clientFd, cMessage, sizeof(cMessage),0);
        cout<<"Client: "<<cMessage<<endl;


        if(!strcmp(cMessage,"Exit"))
        {
            send(clientFd, "Goodbye!", strlen("Goodbye!"), 0);
            cout<<"Client disconnected."<<endl;
            cont=false;
            memset(cMessage,0,sizeof(cMessage));
        }
        else
        {
            memset(cMessage,0,sizeof(cMessage));
            cout<<"Enter message to Client: ";
            cin.get(sMessage,1024,'\n');
            cin.ignore(100,'\n');
            send(clientFd, sMessage, strlen(sMessage), 0);
        }

    }

    closesocket(sockfd);
    WSACleanup();
}
