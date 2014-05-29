/*
* pursuit
* Created Time:  2014年05月02日 星期五 14时16分19秒
* File Name: april.cpp
*/
//#include "april_server.h"
#include "april_protobuf_server.h"

#include <cstdio>

int kRollSize = 500*1000*1000;

boost::scoped_ptr<muduo::AsyncLogging> g_asyncLog;

void asyncOutput(const char* msg, int len)
{
    g_asyncLog->append(msg, len);
}

void setLogging(const char* argv0)
{
    muduo::Logger::setOutput(asyncOutput);
    char name[256];
    strncpy(name, argv0, 256);
    g_asyncLog.reset(new muduo::AsyncLogging(::basename(name), kRollSize));
    g_asyncLog->start();
}

void* reload_dict(void* argv)
{
    April::AprilServer* server = static_cast<April::AprilServer*>(argv);
    server->reload_dict();
}
    
int main(int argc, char** argv)
{
    setLogging(argv[0]);

    LOG_INFO<<"pid = "<<getpid();
    muduo::net::EventLoop loop;
    int port = atoi(argv[1]);
    muduo::net::InetAddress listenAddr(port);
    April::AprilServer server(&loop, listenAddr);
    server.start();
    pthread_t tid;
    pthread_create(&tid, NULL, reload_dict, &server);
    loop.loop();
    pthread_join(tid, NULL);
}
