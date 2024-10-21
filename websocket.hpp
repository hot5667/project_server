#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <string>

class WebSocket {
public:
    static std::string process_handshake(const std::string& request);
    static std::string encode_message(const std::string& message);
    static std::string decode_message(const std::string& frame);
};

#endif // WEBSOCKET_HPP
