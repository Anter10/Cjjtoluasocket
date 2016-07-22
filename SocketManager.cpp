//
//  SocketManager::SocketManager.cpp
//  NewCocosProject2
//
//  Created by 郭有超 on 16/7/21.
//
//



#include "SocketManager.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#include "CCLuaEngine.h"
#include "Socket.h"
#include <list>
#include <string>
using namespace std;

// TCP 管理的socket对象
Socket tcpsocket;

// 函数名称数组  用于在LUA层中调用
string   FUNCTIONS[10] = {"OKS","PVPCALL","CHATCALL"};

//  tcpsocket 用于的功能类型
int      USE_TCPSOCKET_TYPE[10] = {1,2,3,4,5,6,7,8,9,10};
int      CURRENT_USE_SOCKET_TYPE = 0; // 游戏的那个模块使用SOCKET

// TCP 网络线程处理
// Tcp    锁  状态  线程ID
pthread_mutex_t TCP_SOCKET_MUTEX;                              // tcp 当前的状态锁
int             TCP_CURRENT_LINK_STATUE     =   0;             // tcp 当前的连接状态
pthread_t       INIT_TCP_SOCKET_THREAD_ID;                     // tcp 当前的线程ID

// 读取数据 锁 状态  线程ID
pthread_mutex_t READ_SOCKETDATA_MUTEX;                         // TCP 读取数据的锁
int             READ_SOCKETDATA_STATUE      =   0;             // TCP 读取数据的状态
pthread_t       READ_SOCKETDATA_THREAD_ID;                     // TCP 读取数据线程ID

// 发送数据的 锁 状态
pthread_mutex_t SEND_SOCKETDATA_MUTEX;                         // TCP 发送数据的锁
int             SEND_SOCKETDATA_STATUE      =   0;             // TCP 发送数据的状态

// 收到的数据 锁
pthread_mutex_t RECEIVE_SOCKETDATA_MUTEX;

std::list<SMDATA *>    SOCKET_MSG_DATA;                        // 收到消息的数据列表
std::list<SLDATA>      SOCKET_SLD_DATA;                        // 连接的数据列表
std::list<string>      SOCKET_RECEIVEDATA_LIST;                // 收到的数据

// 收到的数据和扩展
char * ReceiveDataLength = (char*)malloc(MAX_MSG_SIZE);
string appendEDL;


SocketManager::~SocketManager(){
   
}

SocketManager::SocketManager(){
    
}

SocketManager::SocketManager(const char * host, unsigned short port){
    tcpsocket.createSocket();
    tcpsocket.Connect(host, port);
    
}

SocketManager::SocketManager(const char * host, unsigned short port, const char * session){
    tcpsocket.createSocket();
    tcpsocket.Connect(host, port, session);
}

SocketManager::SocketManager(const char * host, unsigned short port, const char * session, const char * uid){
    tcpsocket.createSocket();
    tcpsocket.Connect(host, port, session, uid);
}

bool   SocketManager::connectHost(const char * host, unsigned short port){
    tcpsocket.createSocket();
    int connect = tcpsocket.Connect(host, port);
    return connect;
}
 
bool   SocketManager::connectHost(const char * host, unsigned short port, const char * session){
    tcpsocket.createSocket();
    int connect = tcpsocket.Connect(host, port, session);
    return connect;
}

bool   SocketManager::connectHost(const char * host, unsigned short port, const char * session, const char * uid){
    tcpsocket.createSocket();
    int connect = tcpsocket.Connect(host, port, session, uid);
    return connect;
}

void SocketManager::DestroySocket(){
    tcpsocket.Close();
}


// 等待线程
void Sleep(int second){
    usleep(second * 1000);
}

void callGlobalFunc(const char * func, const char * data){
    lua_State * ls = cocos2d::LuaEngine::getInstance()->getLuaStack()->getLuaState();
    try{
       lua_getglobal(ls, func);
       lua_pushstring(ls, data);
       lua_pcall(ls, 1, 0,0);
    }catch(std::exception ex){
        printf("回调失败");
    }
   
}


// 读取数据
bool socketReceiveData(Socket * socket, int timeout){
    long endNum = 0;
    do {
        memset(ReceiveDataLength, 0, MAX_MSG_SIZE);
        pthread_mutex_lock(&RECEIVE_SOCKETDATA_MUTEX);
        endNum = socket->receiveData(ReceiveDataLength);
        appendEDL.append(ReceiveDataLength);
        if(strlen(ReceiveDataLength) < MAX_MSG_SIZE){
           callGlobalFunc(FUNCTIONS[0].c_str(),appendEDL.c_str());
           appendEDL.clear();
        }
        pthread_mutex_unlock(&RECEIVE_SOCKETDATA_MUTEX);
    }while (endNum != -1 && endNum != 0);
    
    return false;
}

void closeTcpSocket(){
    if (tcpsocket.getSockFileDescription() == -1)
    {
        tcpsocket.Close();
    }
}

void* longsocketReadData(void * param){
    try
    {
       socketReceiveData(&tcpsocket,0);
       closeTcpSocket();
    }
    catch (std::exception* e)
    {
        printf("读取数据失败");
    }
    pthread_mutex_lock(&READ_SOCKETDATA_MUTEX);
    READ_SOCKETDATA_STATUE = 0;
    pthread_mutex_unlock(&READ_SOCKETDATA_MUTEX);
    return 0;
    
}


bool initlongsocketReadData()
{
    pthread_mutex_lock(&READ_SOCKETDATA_MUTEX);
    if (READ_SOCKETDATA_STATUE == 1)
    {
        pthread_mutex_unlock(&READ_SOCKETDATA_MUTEX);
        return true;
    }
    READ_SOCKETDATA_STATUE = 1;
    pthread_mutex_unlock(&READ_SOCKETDATA_MUTEX);
    
    pthread_attr_t tAttr;
    int errCode = pthread_attr_init(&tAttr);
    errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    if (errCode!=0)
    {
        pthread_attr_destroy(&tAttr);
        return false;
    }
    
    pthread_create(&READ_SOCKETDATA_THREAD_ID, &tAttr, longsocketReadData, (void *)0);
    pthread_detach(READ_SOCKETDATA_THREAD_ID);
    
    return true;
}



// 初始化当前使用的socket
void * initTcpSocket(void *){
    initlongsocketReadData();
    TCP_CURRENT_LINK_STATUE = 0;
}


bool initTcpSocket()
{
    pthread_mutex_lock(&TCP_SOCKET_MUTEX);
    
    if (TCP_CURRENT_LINK_STATUE == 1)
    {
       pthread_mutex_unlock(&TCP_SOCKET_MUTEX);
        return false;
    }
    TCP_CURRENT_LINK_STATUE = 1;
    pthread_mutex_unlock(&TCP_SOCKET_MUTEX);
 
    pthread_attr_t tAttr;
    int errCode = pthread_attr_init(&tAttr);
    errCode = pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
    if (errCode!=0)
    {
        pthread_attr_destroy(&tAttr);
        return false;
    }
    
    pthread_create(&INIT_TCP_SOCKET_THREAD_ID, &tAttr, initTcpSocket, (void *)0);
    pthread_detach(INIT_TCP_SOCKET_THREAD_ID);
    return true;
}


void SocketManager::CallBackData(){
     initTcpSocket();
}


bool SocketManager::sendData(std::string message){
    if(tcpsocket.getSockFileDescription() != -1){
       pthread_mutex_lock(&SEND_SOCKETDATA_MUTEX);
       tcpsocket.sendData(message.c_str(), strlen(message.c_str()), 0);
       pthread_mutex_unlock(&SEND_SOCKETDATA_MUTEX);
       return true;
    }
    return false;
}














