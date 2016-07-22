//
//  Socket.cpp
//  SocketTest
//
//  Created by 郭有超 on 16/7/19.
//  Copyright © 2016年 郭有超. All rights reserved.
//

#include "Socket.h"
#include <netinet/in.h>


Socket::Socket(){
   
}


Socket::Socket(int sfd){
    sockeFileDescription = sfd;
}


Socket::Socket(const char * ip, unsigned short port){
    sockeFileDescription = createSocket();
    Connect(ip, port);

}



Socket::~Socket(){
    
}


int Socket::createSocket(int addressFaimily, int type, int protocol){
    sockeFileDescription = socket(addressFaimily, type,protocol);
    fcntl(sockeFileDescription, F_SETFL,O_NONBLOCK);
    sockAddr.sin_family = addressFaimily;
    return sockeFileDescription;
}

int Socket::createSocket(){
    sockeFileDescription = socket(IPV4, STREAM, 0);
    sockAddr.sin_family = IPV4;
    return sockeFileDescription;
}

void Socket::Close(){
    shutdown(sockeFileDescription,2);
    close(sockeFileDescription);
    sockeFileDescription  = -1;
}

int Socket::getError(){
    return errno;
}

int Socket::bindAddress(int socketFileDes, sockaddr *addressToBind,int addressStructLength){
    return  bind(socketFileDes, addressToBind, addressStructLength);
}

bool Socket::Listen(int backlogSize){
    
    return false;
}

int Socket::Connect(const char * ip , unsigned short port){
    sockAddr.sin_addr.s_addr = inet_addr(ip);
    sockAddr.sin_port = htons(port);
    int ret = connect(sockeFileDescription, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
    return ret;
}


int Socket::Connect(const char * ip, unsigned short port, const char * session){
    sockAddr.sin_addr.s_addr = inet_addr(ip);
    sockAddr.sin_port = htons(port);
    int ret = connect(sockeFileDescription, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
    this->session = session;
    return ret;

}

int Socket::Connect(const char * ip, unsigned short port, const char * session, const char * uid){
    sockAddr.sin_addr.s_addr = inet_addr(ip);
    sockAddr.sin_port = htons(port);
    int ret = connect(sockeFileDescription, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
    this->session = session;
    this->userid = uid;
    return ret;
}

bool Socket::getHostByName(const char * hostname){
    
    return true;
}


int Socket::sendData(const char * buffer,int bufferLength, int flags){
    ssize_t bytes;
    int count = 0;
    while ( count < bufferLength ) {
        bytes = send(sockeFileDescription, buffer + count, bufferLength - count,0);
        if ( bytes == -1 || bytes == 0 )
            return -1;
        count += bytes;
    }
    return count;
}

int Socket::sendToUdpServer(const char *buffer, int bufferLength, int flags, sockaddr *destinationAddress, int destinationAddressLength){
    return 1;
}

int Socket::receiveFromUDPData(const char *buffer, int bufferLength, int flags, sockaddr *fromAddress, int *fromAddressLength){
    return 1;
}

int Socket::receiveData(const char * buffer){
    return recv(sockeFileDescription, (char *)buffer, MAX_MSG_SIZE, 0);
}

void Socket::setReceiveDataTimeout(int time){
    setsockopt(sockeFileDescription,SOL_SOCKET,SO_RCVTIMEO,(char *)&time,sizeof(int));
}

