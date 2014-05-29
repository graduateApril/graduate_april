/*
* pursuit
* Created Time:  2014年05月05日 星期一 14时10分46秒
* File Name: april_client.cpp
*/
#include "april_protobuf_client.h"
#include "april_request.pb.h"
#include "april_response.pb.h"
#include <cstdio>
#include <google/protobuf/descriptor.h>

namespace April {

AprilClient::AprilClient(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& serverAddr)
    :_loop(loop),
    _client(loop, serverAddr, "AprilClient"),
    _codec(boost::bind(&AprilClient::onProtobufMessage, this, _1, _2, _3))
{
    _client.setConnectionCallback(
            boost::bind(&AprilClient::onConnection, this, _1));
    _client.setMessageCallback(
            boost::bind(&ProtobufCodec::onMessage, &_codec, _1, _2, _3));
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

void AprilClient::write(const muduo::StringPiece& message,
        int id,
        bool sync)
{
    april::response mess;
    mess.set_id(id);
    mess.set_sync(sync);
    _mark = false;
    muduo::MutexLockGuard lock(_mutex);
    if (_connection) {
        //_codec.send(get_pointer(_connection), message);
        _codec.send(_connection, mess);
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

void AprilClient::onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
        const MessagePtr& message,
        muduo::Timestamp)
{
    /*
    april::response mess;
    mess.set_id(1);
    _codec.send(conn, mess);
    */

    const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
    const google::protobuf::FieldDescriptor* id_field = descriptor->FindFieldByName("id");
    const google::protobuf::FieldDescriptor* sync_field = descriptor->FindFieldByName("sync");
        
    const google::protobuf::Reflection* reflection = message->GetReflection();
    _id = reflection->GetInt32(*message, id_field);
    _sync = reflection->GetBool(*message, sync_field);
    LOG_INFO << "receive - id " << _id << " sync "<< _sync; 
    _mark = true;
}
    

}

