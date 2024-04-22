#include "Client.hpp"
const std::string Client::DEF_SERVER_IP = "127.0.0.1";

Client::status_code_t Client::init(const std::string& server_ip, const uint16_t& server_port, const std::string client_name, const uint16_t& period)
{
    
    __name = client_name;
    __period = period;
    
    inet_aton(server_ip.c_str(),&__server_address.sin_addr);
    __server_address.sin_port = htons(server_port);
    __server_address.sin_family = AF_INET;

    return SUCCESS;
}
Client::status_code_t Client::start()
{
    int buffer_time_size = sizeof("yyyy-mm-dd hh:mm:ss.");
    char buffer_time[buffer_time_size];
    std::string data;
    std::timespec time_now;
    if(__period == 0 || __name == ""){
        std::cerr << "ERROR period or name is not initialized" << std::endl;
        return FAIL_EXECUTE;
    }
    while(1)
    {
        __socket = socket(PF_INET,SOCK_STREAM,0);
        if(__socket < 0){
            std::cerr << "ERROR in socket, errno = " << strerror(errno) << std::endl;
            return FAIL_EXECUTE;
        }
        if(connect(__socket,(sockaddr*)&__server_address,__server_length_address) == -1){
            std::cerr << "ERROR in connect, errno = " << strerror(errno) << std::endl;
            return FAIL_EXECUTE;
        }

        data = '[';
        std::fill_n(buffer_time,buffer_time_size,0);

        std::timespec_get(&time_now, TIME_UTC);
        std::strftime(buffer_time,buffer_time_size,"%Y-%m-%d %H:%M:%S.",std::gmtime(&time_now.tv_sec));
        data += buffer_time;
        data += std::to_string(time_now.tv_nsec / 1'000'000);
        data += "] " + __name;
        if(send(__socket,data.c_str(), data.size(),0) == -1){
            std::cerr << "ERROR in send, errno = " << strerror(errno) << std::endl;
            return FAIL_EXECUTE;
        }
        send(__socket,"[end]",sizeof("[end]"),0);
        shutdown(__socket,SHUT_RDWR);
        sleep(__period);
    }

    return SUCCESS;
}