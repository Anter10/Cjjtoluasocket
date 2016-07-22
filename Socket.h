//
//  Socket.hpp
//  SocketTest
//
//  Created by 郭有超 on 16/7/19.
//  Copyright © 2016年 郭有超. All rights reserved.
//

#ifndef Socket_hpp
#define Socket_hpp


// 类型


#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
 
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include "errno.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

 

// TCP , UDP 创建
#define IPV4       AF_INET
// IPV6创建
#define IPV6       AF_INET6

// Socket 类型 @SOCK_STREAM流式套接字
#define STREAM     SOCK_STREAM
#define DGRAM      SOCK_DGRAM

// socket 的协议类型 TCP UDP
#define TCP        IPPROTO_TCP
#define UDP        IPPROTO_UDP

// 监听连接失败
#define LISTEN_ERROR  SOCKET_ERROR

// Socket文件描述
#define SOCKET_FILE_DESCRIPTION 1


#define SHUTTYPE   2

#define MAX_MSG_SIZE 10 * 1024		// 最大消息数量
#define BLOCKSECONDS	30			//

#define SOCKET int

#define SUCCESS  0
#define ERROR   -1

typedef struct sockaddr_in SOCKADDRS;

struct SMData{
    std::string _sendstr;
    std::string _host;
    int _port;
    std::string _class;
};

struct SLData{
    std::string _host;
    int _port;
    std::string _class;
};

typedef struct SLData SLDATA;
typedef struct SMData SMDATA;



class Socket{
private:
    SOCKADDRS      sockAddr;
    int            sockeFileDescription = 0;  // 文件描述
    int            receiveTimeOut       = 5;  // 监听接收超时
    const char     * session;                 // 用户Session
    const char     * userid;                  // 用户userid
    bool           isconnect            = false; // Socket连接状态
public:
    // 构造函数
    Socket();
    
    //sfd 文件描述符
    Socket(int sfd);
    
    Socket(const char * ip, unsigned short port);
    
    // 析构函数
    ~Socket();
    
    // 创建Socket 返回值为－1表示创建失败
    // @addressFaimily    socket的IP 类型 IPV4 IPV6
    // @type              socket 的类型
    // @protocol          协议类型
    int createSocket(int addressFaimily, int type, int protocol);
    
    //  不带参数的创建SOCKET
    int createSocket();
    
    // 关闭socket
    void Close();
    
    
    // 绑定IP 端口  udp 是无连接的绑定就可用  tcp 需要Listen 监听连接是否成功
    // @socketFileDes       socket文件描述
    // @sockaddr            相关地址
    // @addressStructLength 地址长度
    // 成功绑定返回0，失败返回 -1
    int bindAddress(int socketFileDes, sockaddr *addressToBind,int addressStructLength);
    
    
    // TCP 监听连接
    // @backlogSize          5
    // 成功返回true 失败返回false
    bool Listen(int backlogSize);
    
    // 连接相应的地址
    // @ip   绑定的IP地址
    // @port 相应地址的端口
    // 连接成功返回0，失败返回 -1。
    int Connect(const char * ip, unsigned short port);
    
    // 连接相应的地址
    // @ip   绑定的IP地址
    // @port 相应地址的端口
    // @session 用户的session
    // 连接成功返回0，失败返回 -1。
    int Connect(const char * ip, unsigned short port, const char * session);
    
    // 连接相应的地址
    // @ip   绑定的IP地址
    // @port 相应地址的端口
    // @session 用户的session
    // @uid  用户的ID
    // 连接成功返回0，失败返回 -1。
    int Connect(const char * ip, unsigned short port, const char * session, const char * uid);
    
    // DNS 解析
    // @hostname 主机的名称
    // 找到返回主机名  反之返回NULL
    bool  getHostByName(const char * hostname);
    
    // 发送数据
    // @buffer       发送的数据
    // 发送成功返回已经发送的数据长度 反之返回-1
    int sendData(const char * buffer,int bufferLength, int flags);
    
 
    
    // 发送数据
    // @buffer       接收到的数据
    // 发送成功返回已经发送的数据长度 反之返回-1
    int receiveData(const char * buffer);
    
    int getError(void);
 
    // 使用UDP发送报文数据
    // @buffer                       UDP发送的数据
    // @bufferLength                 UDP发送的数据长度
    // @flags                        UDP发送的标示
    // @destinationAddress           UDP发送的目的地址
    // @destinationAddressLength     UDP发送的目的地址长度
    // 发送成功返回发送成功的字节数 反之返回-1
    int sendToUdpServer(const char *buffer, int bufferLength, int flags, sockaddr *destinationAddress, int destinationAddressLength);
    
    // 使用UDP发送报文数据
    // @buffer                       UDP接收数据
    // @bufferLength                 UDP接收的数据长度
    // @flags                        UDP接收的标示
    // @destinationAddress           UDP接收的目的地址
    // @destinationAddressLength     UDP接收的目的地址长度
    // 读取成功返回成功读取的字节数，否则返回 -1 。
    int receiveFromUDPData(const char *buffer, int bufferLength, int flags, sockaddr *fromAddress, int *fromAddressLength);
    
    
    //获得数据接收超时时间
    // @time 超时时间
    void setReceiveDataTimeout(int time);
    
    
    // 获得文件描述符
    int getSockFileDescription(){
        return this->sockeFileDescription;
    }
    
    // 获得当前连接地址描述
    SOCKADDRS  getSockaddr(){
        return this->sockAddr;
    }
    
    
    // 设置文件描述符
    void setSockFileDescription(int sfd){
        this->sockeFileDescription = sfd;
    }
    
    // 设置文件描述符
    void setSockaddr(SOCKADDRS   akd){
        this->sockAddr = akd;
    }
    
    
    // 获得端口
    inline int getPort(){
        return sockAddr.sin_port;
    }
    
    
    // 获得连接状态
    bool isConnect(){
        return isconnect;
    }
    
    // 设置连接状态
    // @connect socket是否连接 false表示还没有连接 true为连接状态
    void setIsConnect(bool connect){
        isconnect = connect;
    }
    
    // 获得连接状态
    // 返回false表示还没有连接 true为连接状态
    bool getIsConnect(void){
        return isconnect;
    }
    
};

#endif /* Socket_hpp */






































