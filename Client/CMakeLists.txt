add_library(Client STATIC "Client.cpp")

add_executable(appClient "main.cpp")

target_link_libraries(appClient PUBLIC Client)