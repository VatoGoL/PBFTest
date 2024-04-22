#include "Client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Слишком мало параметров для запуска приложения введите команду --help или -h для просмотра дополнительных сведений" << std::endl;
        return EXIT_FAILURE;
    }
    std::string parameters;
    std::string name = "";
    uint16_t port = 0;
    uint16_t period_s = 0;
    for(int i = 1; i < argc; i++){
        parameters = argv[i];
        if(parameters == "--help" || parameters == "-h")
        {
            std::cout << "Программе требуется следующий параметр:" << std::endl
                      << "1. Порт: --port <Порт> или -p <Порт>" << std::endl
                      << "2. Имя клиента: --name <Имя> или -n <Имя>" << std::endl
                      << "3. Период отправки сообщений в секундах: --period <Период> или -per <Период>" << std::endl;
            return EXIT_SUCCESS;
        }else if(parameters == "--port" || parameters == "-p")
        {
            port = std::stoi(argv[++i]);
        }else if(parameters == "--name" || parameters == "-n"){
            name = argv[++i];
        }else if(parameters == "--period" || parameters == "-per"){
            period_s = std::stoi(argv[++i]);
        }
    }   
    if(period_s == 0 || name == "" || port == 0){
        std::cerr <<"ERROR parameters: "<<"[ " << port <<" "<< name << " "<< period_s << "]"<<std::endl;    
        return EXIT_FAILURE;
    }
    Client client;
    if(client.init(Client::DEF_SERVER_IP, port, name, period_s) == Client::FAIL_INIT){
        return EXIT_FAILURE;
    }
    if(client.start() == Client::FAIL_EXECUTE){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}