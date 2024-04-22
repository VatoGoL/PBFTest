#include <string>
#include "Server.hpp"

int main(int argc, char* argv[])
{

    if(argc < 2){
        std::cerr << "Слишком мало параметров для запуска приложения введите команду --help или -h для просмотра дополнительных сведений" << std::endl;
        return EXIT_FAILURE;
    }
    std::string parameters;
    uint16_t port = 0;
    for(int i = 1; i < argc; i++){
        parameters = argv[i];
        if(parameters == "--help" || parameters == "-h")
        {
            std::cout << "Программе требуется следующий параметр:" << std::endl
                      << "1. Порт: --port <Порт> или -p <Порт>" << std::endl;
            return EXIT_SUCCESS;
        }else if(parameters == "--port" || parameters == "-p")
        {
            port = std::stoi(argv[++i]);
        }
    }

    if(port == 0){
        std::cerr <<"ERROR parameters: "<<"[ " << port <<std::endl;    
        return EXIT_FAILURE;
    }
    uint8_t max_queue_size = 1;
    try{
        Logger::init(max_queue_size);
    }catch(Logger::error_logger_t &e){
        if(e == Logger::FILE_NOT_OPEN){
            std::cerr << "Log file not open" << std::endl;
        }
        return EXIT_FAILURE;
    }

    Server server;
    if(server.init(port) == Server::FAIL_INIT){
        return EXIT_FAILURE;
    }
    if(server.start() == Server::FAIL_EXECUTE){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}