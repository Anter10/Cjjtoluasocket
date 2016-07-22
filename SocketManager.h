//
//  SocketManager.hpp
//  NewCocosProject2
//
//  Created by 郭有超 on 16/7/21.
//
//

#ifndef SocketManager_hpp
#define SocketManager_hpp

#include <stdio.h>
#include <string>
#include "pthread.h"

using namespace std;
 

class SocketManager{
private:
    
    
public:
    
    ~SocketManager();
    
    SocketManager();
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    SocketManager(const char * host, unsigned short port);
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    // @session 当前玩家的session
    SocketManager(const char * host, unsigned short port, const char * session);
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    // @session 当前玩家的session
    // @uid     当前玩家的ID
    SocketManager(const char * host, unsigned short port, const char * session, const char * uid);
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    bool   connectHost(const char * host, unsigned short port);
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    // @session 当前玩家的session
    bool   connectHost(const char * host, unsigned short port, const char * session);
    
    // 参数说明
    // @host 服务器IP地址
    // @port 服务器端口地址
    // @session 当前玩家的session
    // @uid     当前玩家的ID
    bool   connectHost(const char * host, unsigned short port, const char * session, const char * uid);
    
    
    // 关闭socket连接
    void DestroySocket();
    
    // 开始网络请求回调
    void CallBackData();
    
    
    // 发送数据
    // @message 发送的数据
    // 返回false表示发送失败 反之成功
    bool sendData(std::string message);
};

// 对网络请求进行多线程处理


#endif /* SocketManager_hpp */
