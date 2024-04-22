#include "Server.hpp"

const uint8_t Server::LISTEN_MAX = 10;
const uint16_t Server::__BUFFER_SIZE = 256;
Server::status_code_t Server::init(uint16_t port)
{

    __socket = socket(PF_INET,SOCK_STREAM,0);
    if(__socket < 0){
        std::cerr << "ERROR in socket, errno = " << strerror(errno) << std::endl;
        return FAIL_INIT;
    }

    std::fill_n((char*)&__address,sizeof(__address),0);
    __address.sin_family = AF_INET;
    __address.sin_addr.s_addr = htonl(INADDR_ANY);
    __address.sin_port = htons(port);

    if(bind(__socket, (sockaddr*)&__address, sizeof(__address)) != 0){
        std::cerr << "ERROR in bind, errno = " << strerror(errno) << std::endl;
        return FAIL_INIT;
    }

    if(getsockname(__socket, (sockaddr*)&__address, (socklen_t*)&__length_address) != 0){
        std::cerr << "ERROR in getsockname, errno = " << strerror(errno) << std::endl;
        return FAIL_INIT;
    }

    if(listen(__socket, LISTEN_MAX) != 0){
        std::cerr << "ERROR in listen, errno = " << strerror(errno) << std::endl;
        return FAIL_INIT;
    }
    return SUCCESS;
}
Server::status_code_t Server::start()
{
    if(__socket < 0){
        std::cerr << "ERROR the socket is not initialized" << std::endl;
        return FAIL_EXECUTE;
    }
    int client_socket;
    sockaddr_in address_client;
    socklen_t length_address;
    while(1)
    {
        client_socket = accept(__socket, (sockaddr*)&address_client, (socklen_t*)&length_address);
        std::thread(&Server::__clientWorker,&(*this), client_socket).detach();
    }
    return SUCCESS;
}
void Server::__clientWorker(int socket)
{
    char buffer[__BUFFER_SIZE];
    std::fill_n(buffer,__BUFFER_SIZE, 0);
    std::string data = "";
    std::string message = "";
    size_t exit_pos;
    while(recv(socket,&buffer,__BUFFER_SIZE,0) > 0)
    {
        data = buffer;
        exit_pos = data.find("[end]");
        if(exit_pos != std::string::npos){
            data.erase(exit_pos,sizeof("[end]"));
            message += data;
            __mutex.lock();
            Logger::writeLog("Server","__clientWorker",Logger::log_message_t::EVENT,message);
            __mutex.unlock();
            break;
        }
        message += data;
        
        
        
        
    }
    shutdown(socket,SHUT_RDWR);
}