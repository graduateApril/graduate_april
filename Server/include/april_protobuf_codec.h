/*
* pursuit
* Created Time:  2014年05月03日 星期六 21时00分56秒
* File Name: april_protobuf_codec.h
*/
#ifndef APRIl_CODEC_H
#define APRIL_CODEC_H

#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <google/protobuf/message.h>

namespace April{

typedef boost::shared_ptr<google::protobuf::Message> MessagePtr;

class ProtobufCodec : boost::noncopyable 
{
public:
    enum ErrorCode {
        kNoError = 0,
        kInvalidLength,
        kCheckSumError,
        kInvalidNameLen,
        kUnknownMessageType,
        kParseError,
    };  
    
    typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
            const MessagePtr&,
            muduo::Timestamp)> ProtobufMessageCallback;
    typedef boost::function<void (const muduo::net::TcpConnectionPtr&,
            muduo::net::Buffer*,
            muduo::Timestamp,
            ErrorCode)> ErrorCallback;
    
    explicit ProtobufCodec(const ProtobufMessageCallback& messageCb)
        :_messageCallback(messageCb),
        _errorCallback(defaultErrorCallback)
    {
    }
    
    ProtobufCodec(const ProtobufMessageCallback& messageCb, const ErrorCallback& errorCb)
        :_messageCallback(messageCb),
        _errorCallback(errorCb)
    {
    }
    
    void onMessage(const muduo::net::TcpConnectionPtr& conn,
            muduo::net::Buffer* buf,
            muduo::Timestamp receiveTime);
    
    void send(const muduo::net::TcpConnectionPtr& conn,
            const google::protobuf::Message& message)
    {
        muduo::net::Buffer buf;
        fillEmptyBuffer(&buf, message);
        conn->send(&buf);
    }
    
    static const muduo::string& errorCodeToString(ErrorCode errorCode);
    static void fillEmptyBuffer(muduo::net::Buffer* buf, const google::protobuf::Message& message);
    static google::protobuf::Message* createMessage(const std::string& type_name);
    static MessagePtr parse(const char* buf, int len, ErrorCode* errorCode);

private:
    static void defaultErrorCallback(const muduo::net::TcpConnectionPtr&,
            muduo::net::Buffer*,
            muduo::Timestamp,
            ErrorCode);
    
    ProtobufMessageCallback _messageCallback;
    ErrorCallback _errorCallback;

    const static int kHeaderLen = sizeof(int32_t);
    const static int kMinMessageLen = 2 * kHeaderLen + 2;
    const static int kMaxMessageLen = 64*1024*1024;
};

} // namespace April

#endif // APRIL_CODEC_H
