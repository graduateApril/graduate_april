/*
* pursuit
* Created Time:  2014年05月05日 星期一 13时45分43秒
* File Name: april_protobuf_client.h
*/

#ifndef APRIL_PROTOBUF_CLIENT_H
#define APRIL_PROTOBUF_CLIENT_H

#include "april_protobuf_codec.h"
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
    void write(const muduo::StringPiece& message, int, bool);

    int get_id() {
        return _id;
    }
    
    bool get_sync() {
        return _sync;
    }
    
    bool get_mark() {
        return _mark;
    }
    
    bool is_connected() 
    {
        muduo::MutexLockGuard lock(_mutex);
        bool ret = _connection->connected();
        return ret;
    }
private:
    void onConnection(const muduo::net::TcpConnectionPtr& conn);
    
    void onStringMessage(const muduo::net::TcpConnectionPtr&,
            const muduo::string&,
            muduo::Timestamp time);

    void onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
            const MessagePtr& message,
            muduo::Timestamp time);

    muduo::net::EventLoop* _loop;
    muduo::net::TcpClient _client;
    ProtobufCodec _codec;
    muduo::MutexLock _mutex;
    muduo::net::TcpConnectionPtr _connection;
    int _id;
    bool _sync;

    bool _mark;
};

} // namespace April
#endif // APRIL_PROTOBUF_CLIENT_H

