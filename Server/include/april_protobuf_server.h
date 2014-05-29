/*
* pursuit
* Created Time:  2014年05月02日 星期五 13时55分20秒
* File Name: april_protobuf_server.h
*/

#ifndef APRIL_PROTOBUF_SERVER_H
#define APRIL_PROTOBUF_SERVER_H

#include "april_protobuf_codec.h"
#include <muduo/net/TcpServer.h>

#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>
#include "dict.cpp"
#include <pthread.h>

namespace April{

class AprilServer{
public:
    AprilServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr);
    
    void start();
    ~AprilServer();

    void reload_dict();
    
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
            muduo::net::Buffer* buf,
            muduo::Timestamp time);

    void onStringMessage(const muduo::net::TcpConnectionPtr& conn,
            const muduo::string& message,
            muduo::Timestamp time);

    void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
            const MessagePtr& message,
            muduo::Timestamp time);


private:
    muduo::net::EventLoop* _loop;
    muduo::net::TcpServer _server;
    ProtobufCodec _codec;
    Dict<int, int>* _dict;
    bool _sync;
};

} // namespace April

#endif // APRIL_PROTOBUF_SERVER_H
