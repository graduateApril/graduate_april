/*
* pursuit
* Created Time:  2014年05月05日 星期一 13时45分43秒
* File Name: april_client.h
*/

#ifndef APRIL_CLIENT_H
#define APRIL_CLIENT_H

#include "april_codec.h"
#include <muduo/net/TcpClient.h>

#include <muduo/base/Mutex.h>
#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/EventLoopThread.h>

#include <boost/bind.hpp>

namespace April {

class AprilClient: boost::noncopyable {
public:
    AprilClient(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& serverAddr);
    
    void connect();
    void disconnect();
    void write(const muduo::StringPiece& message);
    
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    
    void onStringMessage(const muduo::net::TcpConnectionPtr&,
            const muduo::string&,
            muduo::Timestamp time);
    
    muduo::net::EventLoop* _loop;
    muduo::net::TcpClient _client;
    AprilCodec _codec;
    muduo::MutexLock _mutex;
    muduo::net::TcpConnectionPtr _connection;
};

} // namespace April
#endif // APRIL_CLIENT_H

