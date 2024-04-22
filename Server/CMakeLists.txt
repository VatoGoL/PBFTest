link_directories(../)

add_executable(appServer "main.cpp")

add_library(Server STATIC "Server.cpp")

target_link_libraries(Server PRIVATE Logger)
target_link_libraries(appServer PUBLIC Server)