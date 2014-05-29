/*
* pursuit
* Created Time:  2014年05月02日 星期五 14时16分19秒
* File Name: april.cpp
*/
#include "april_protobuf_client.h"

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

bool syncclinet;
bool mark[10];
April::AprilClient* c[10];

void* check(void* argv) 
{
    while (1) {
        int cnt = 0;
        for (int i = 0; i < 2; i++)
            if (c[i]->get_sync() == !syncclinet) {
                cnt++;
            }
        if (cnt == 2) {
            syncclinet = !syncclinet;
        } 
        sleep(5); 
    } 
}
    
    
int main(int argc, char** argv)
{
    setLogging(argv[0]);

    LOG_INFO<<"pid = "<<getpid();
    muduo::net::EventLoopThread loopThread;
    muduo::net::InetAddress serverAddr(2007);
    April::AprilClient client(loopThread.startLoop(), serverAddr);
    client.connect();
    

    muduo::net::EventLoopThread loopThread1;
    muduo::net::InetAddress serverAddr1(2008);
    April::AprilClient client1(loopThread1.startLoop(), serverAddr1);
    client1.connect();

    c[0] = &client;
    c[1] = &client1;

    syncclinet = false;
    int id;
    memset(mark, false, sizeof mark);
    
    pthread_t pid;
    pthread_create(&pid, NULL, check, NULL);

    std::string line;
    int cnt = 0;
    while (std::cin >> line >> id) {
        for (int i = 0; i < 2; i++) {
            cnt++;
            cnt %= 2;
            i = cnt;
            if (mark[i] = c[i]->is_connected()) {
                c[i]->write(line, id, syncclinet);
                LOG_INFO << "client " << i;
                break;
            }
        }
    }
    client.disconnect();
    client1.disconnect();
}
