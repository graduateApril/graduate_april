/*
* pursuit
* Created Time:  2014年05月02日 星期五 14时06分01秒
* File Name: april_protobuf_server.cpp
*/
#include "april_protobuf_server.h"
#include "april_response.pb.h"
#include <google/protobuf/descriptor.h>

namespace April{

int dict_parse_func(char* tokens[],
        unsigned int token_num,
        int* key, 
        int* value)
{
    if (token_num != 2) {
        LOG_ERROR << "token_num is not equal to 2";
        return -1;
    }
    
    *key = atoi(tokens[0]);
    *value = atoi(tokens[1]);
    return 0;
}

AprilServer::AprilServer(muduo::net::EventLoop* loop,
        const muduo::net::InetAddress& listenAddr)
    :_loop(loop),
    _server(loop, listenAddr, "AprilServer"),
    _codec(boost::bind(&AprilServer::onProtobufMessage, this, _1, _2, _3)),
    _sync(false)
{
    _server.setConnectionCallback(
            boost::bind(&AprilServer::onConnection, this, _1));
    _server.setMessageCallback(
            boost::bind(&ProtobufCodec::onMessage, &_codec, _1, _2, _3));
    _dict = new(std::nothrow) Dict<int, int>("data.sign", 100, dict_parse_func);
    _dict->load_dict();
}

AprilServer::~AprilServer()
{
    if (_dict) {
        delete _dict;
    }
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
    //_codec.send(get_pointer(conn), message);
}

void AprilServer::onProtobufMessage(const muduo::net::TcpConnectionPtr& conn,
        const MessagePtr& message,
        muduo::Timestamp time)
{

    const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
    const google::protobuf::FieldDescriptor* id_field = descriptor->FindFieldByName("id");
    const google::protobuf::FieldDescriptor* sync_field = descriptor->FindFieldByName("sync");

    const google::protobuf::Reflection* reflection = message->GetReflection();
    int32_t id = reflection->GetInt32(*message, id_field);
    bool sync = reflection->GetBool(*message, sync_field);
    LOG_INFO << "receive - id " << id << " sync " << sync;

    if (_sync && sync) {
        _dict->swap_dict();
        _sync = false;
    }

    april::response mess;
    int value = 0;
    _dict->seek(id, &value);
    mess.set_id(value);
    mess.set_sync(_sync);
    _codec.send(conn, mess);
    
}

void AprilServer::reload_dict()
{
    while (1) {
        if (!_sync && _dict->reload_dict() == 0) {
            _sync = true;
        }
        sleep(5);
    }
}

} // namespace April
