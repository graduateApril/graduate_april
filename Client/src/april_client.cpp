/*
* pursuit
* Created Time:  2014年05月05日 星期一 14时10分46秒
* File Name: april_client.cpp
*/
#include "april_client.h"
#include <cstdio>

namespace April {

AprilClient::AprilClient(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& serverAddr)
    :_loop(loop),
    _client(loop, serverAddr, "AprilClient"),
    _codec(boost::bind(&AprilClient::onStringMessage, this, _1, _2, _3))
{
    _client.setConnectionCallback(
            boost::bind(&AprilClient::onConnection, this, _1));
    _client.setMessageCallback(
            boost::bind(&AprilCodec::onMessage, &_codec, _1, _2, _3));
    _client.enableRetry();
}

void AprilClient::connect()
{
    _client.connect();
}

void AprilClient::disconnect()
{
    // _client.disconnect();
}

void AprilClient::write(const muduo::StringPiece& message)
{
    muduo::MutexLockGuard lock(_mutex);
    if (_connection) {
        _codec.send(get_pointer(_connection), message);
    }
}

void AprilClient::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO<<conn->localAddress().toIpPort() << " -> "
        << conn->peerAddress().toIpPort() <<" is "
        <<(conn->connected() ? " UP ":" DOWN ");
    
    muduo::MutexLockGuard lock(_mutex);
    if (conn->connected()) {
        _connection = conn;
    } else {
        _connection.reset();
    }
}

void AprilClient::onStringMessage(const muduo::net::TcpConnectionPtr&, 
        const muduo::string& message,
        muduo::Timestamp)
{
    printf("<<< %s\n", message.c_str());
}

}

