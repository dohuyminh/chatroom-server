#pragma once

namespace HTTPChatroomServer {

class ServerState {
public:
    static ServerState& access();
    bool isRunning();
    void setRunning();
    void setStop();

private:
    ServerState();

private:
    bool _isRunning;
};

}