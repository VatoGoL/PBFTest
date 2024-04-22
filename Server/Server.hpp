#pragma once
#include <sys/socket.h>
#include <resolv.h>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <cstring>
#include "../Logger/Logger.hpp"

class Server{
public:
    enum status_code_t
    {
        SUCCESS = 0,
        FAIL_INIT,
        FAIL_EXECUTE   
    };
    static const uint8_t LISTEN_MAX;
    status_code_t init(uint16_t port);
    status_code_t start();
private:
    int __socket = -1;
    sockaddr_in __address;
    socklen_t __length_address;
    static const uint16_t __BUFFER_SIZE;

    std::mutex __mutex;

    void __clientWorker(int socket);
};