#include "server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>

ChatServer::ChatServer() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_socket, (struct sockaddr*)&address, sizeof(address));
}

void ChatServer::run(uint16_t port) {
    listen(server_socket, 3);
    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        int addrlen = sizeof(address);
        int new_socket = accept(server_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);

        if (new_socket >= 0) {
            std::cout << "New client connected!" << std::endl;
            clients.insert(new_socket);

            std::thread(&ChatServer::handle_client, this, new_socket).detach();
        }
    }
}

void ChatServer::handle_client(int client_socket) {
    char buffer[1024] = {0};
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_socket, buffer, 1024);
        if (valread <= 0) {
            std::cout << "Client disconnected!" << std::endl;
            close(client_socket);
            clients.erase(client_socket);
            break;
        }

        std::string message(buffer);
        broadcast_message(message);
    }
}

void ChatServer::broadcast_message(const std::string& message) {
    for (int client : clients) {
        send(client, message.c_str(), message.size(), 0);
    }
}
