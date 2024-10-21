#include "websocket.hpp"
#include <iostream>
#include <openssl/sha.h>
#include <base64.h>

std::string WebSocket::process_handshake(const std::string& request) {
    std::string key = extract_websocket_key(request);
    std::string accept_key = base64_encode(SHA1(key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"));
    
    return "HTTP/1.1 101 Switching Protocols\r\n"
           "Upgrade: websocket\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Accept: " + accept_key + "\r\n\r\n";
}

std::string WebSocket::encode_message(const std::string& message) {
    // WebSocket 프레임으로 메시지를 인코딩
    return "\x81" + std::string(1, message.size()) + message;
}

std::string WebSocket::decode_message(const std::string& frame) {
    // WebSocket 프레임에서 메시지를 디코딩
    return frame.substr(2);
}
