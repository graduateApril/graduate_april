/*
* pursuit
* Created Time:  2014年05月02日 星期五 13时55分20秒
* File Name: april.h
*/

#ifndef _APRIL_SERVER_H_
#define _APRIL_SERVER_H_

#include "april_codec.h"
#include <muduo/net/TcpServer.h>

#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>

namespace April{

class AprilServer{
public:
    AprilServer(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& listenAddr);
    
    void start();
    
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
            muduo::net::Buffer* buf,
            muduo::Timestamp time);

    void onStringMessage(const muduo::net::TcpConnectionPtr& conn,
            const muduo::string& message,
            muduo::Timestamp time);

private:
    muduo::net::EventLoop* _loop;
    muduo::net::TcpServer _server;
    AprilCodec _codec;
};

} // namespace April

#endif // _APRIL_SERVER_H
