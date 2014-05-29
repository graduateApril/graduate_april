/*
* pursuit
* Created Time:  2014年05月02日 星期五 15时19分47秒
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
