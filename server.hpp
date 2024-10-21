#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
#include <set>

class ChatServer {
public:
    ChatServer();
    void run(uint16_t port);
    void handle_client(int client_socket);

private:
    int server_socket;
    std::set<int> clients;
    struct sockaddr_in address;
    void broadcast_message(const std::string& message);
};

#endif 
