/*
* pursuit
* Created Time:  2014��05��02�� ������ 15ʱ19��47��
* File Name: may_client.h
*/
#ifndef _MAY_CLIENT_H
#define _MAY_CLIENT_H

#include <muduo::net::TcpClietn>
#include <

namespace May{
    
class MayClient{
public:
    MayClient(EventLoop* loop, const InetAddress& serverAddr)
        :_loop(loop),
        _client(loop, serverAddr, "MayClient"),
        _codec(boost::bind(&MayClient
        
};

} // namespace May
#endif
