#pragma once
#include <sys/socket.h>
#include <resolv.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
class Client{
public:
    static const std::string DEF_SERVER_IP;
    
    enum status_code_t
    {
        SUCCESS = 0,
        FAIL_INIT,
        FAIL_EXECUTE   
    };

    status_code_t init(const std::string& server_ip, const uint16_t& server_port, const std::string client_name, const uint16_t& period);
    status_code_t start();
private:
    std::string __name;
    uint8_t __period;
    int __socket = -1;
    sockaddr_in __server_address;
    socklen_t __server_length_address = sizeof(__server_address);
};