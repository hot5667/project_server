#include "server.hpp"

int main() {
    ChatServer server;
    server.run(8080);
    return 0;
}