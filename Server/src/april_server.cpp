/*
* pursuit
* Created Time:  2014年05月02日 星期五 14时06分01秒
* File Name: april_server.cpp
*/
#include "april_server.h"

namespace April{

AprilServer::AprilServer(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& listenAddr)
    :_loop(loop),
    _server(loop, listenAddr, "AprilServer"),
    _codec(boost::bind(&AprilServer::onStringMessage, this, _1, _2, _3))
{
    _server.setConnectionCallback(
            boost::bind(&AprilServer::onConnection, this, _1));
    _server.setMessageCallback(
            boost::bind(&AprilCodec::onMessage, &_codec, _1, _2, _3));
}

void AprilServer::start()
{
    _server.start();
}

void AprilServer::onConnection(const muduo::net::TcpConnectionPtr& conn)
{
    LOG_INFO<<"AprilServer - "<<conn->peerAddress().toIpPort()<<" -> "
        <<conn->localAddress().toIpPort()<<" is "
        <<(conn->connected()?"UP":"DOWN");
}

void AprilServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buf,
        muduo::Timestamp time)
{
    muduo::string msg(buf->retrieveAllAsString());
    LOG_INFO<<conn->name()<<" echo "<<msg.size()<<" bytes, "
        <<"data received at "<<time.toString();
    conn->send(msg);
}

void AprilServer::onStringMessage(const muduo::net::TcpConnectionPtr& conn, 
        const muduo::string& message,
        muduo::Timestamp time)
{
    _codec.send(get_pointer(conn), message);
}

} // namespace April
