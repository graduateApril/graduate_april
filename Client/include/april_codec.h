/*
* pursuit
* Created Time:  2014年05月03日 星期六 21时00分56秒
* File Name: april_codec.h
*/
#ifndef APRIl_CODEC_H
#define APRIL_CODEC_H

#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>


#include <google/protobuf/message.h>

namespace April {

class AprilCodec : boost::noncopyable {
public:
    typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
            const muduo::string& message,
            muduo::Timestamp)> StringMessageCallback;
    
    explicit AprilCodec(const StringMessageCallback& cb)
        :_messageCallback(cb)
    {
    }
    
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
            muduo::net::Buffer* buf,
            muduo::Timestamp receiveTime);
    
    void send(muduo::net::TcpConnection* conn,
            const muduo::StringPiece& message);
    
private:
    StringMessageCallback _messageCallback;

    const static size_t kHeaderLen = sizeof(int32_t);
};

} // namespace April

#endif // APRIL_CODEC_H
