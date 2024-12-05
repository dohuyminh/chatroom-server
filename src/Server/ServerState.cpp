#include "ServerState.h"

namespace HTTPChatroomServer {
    
ServerState::ServerState() : _isRunning(false) {}

ServerState& ServerState::access() {
    static ServerState state;
    return state;
}

bool ServerState::isRunning() {
    return _isRunning;
}

void ServerState::setRunning() {
    _isRunning = true;
}

void ServerState::setStop() {
    _isRunning = false;
}

}