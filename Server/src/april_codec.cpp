/*
* pursuit
* Created Time:  2014年05月03日 星期六 21时50分54秒
* File Name: april_codec.cpp
*/

#include "april_codec.h"

namespace April{

void AprilCodec::onMessage(const muduo::net::TcpConnectionPtr& conn,
        muduo::net::Buffer* buf,
        muduo::Timestamp receiveTime)
{
    while (buf->readableBytes() >= kHeaderLen) {
        const void* data = buf->peek();
        int32_t be32 = *static_cast<const int32_t*>(data);
        const int32_t len = muduo::net::sockets::networkToHost32(be32);
        if (len > 65536 || len < 0) {
            LOG_ERROR<<"Invalid length "<<len;
            conn->shutdown();
            break;
        } else if (buf->readableBytes() >= len + kHeaderLen) {
            buf->retrieve(kHeaderLen);
            muduo::string message(buf->peek(), len);
            _messageCallback(conn, message, receiveTime);
            buf->retrieve(len);
        } else {
            break;
        }
    }
}

void AprilCodec::send(muduo::net::TcpConnection* conn,
        const muduo::StringPiece& message)
{
    muduo::net::Buffer buf;
    buf.append(message.data(), message.size());
    int32_t len = static_cast<int32_t>(message.size());
    int32_t be32 = muduo::net::sockets::hostToNetwork32(len);
    buf.prepend(&be32, sizeof be32);
    conn->send(&buf);
}
        
} // namespace April
