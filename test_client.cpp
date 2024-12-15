#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: ./<executable> <Client's IP address> <port>\n";
        std::exit(-1);
    }
    
    int sockfd, nbytes;
    int rv;
    addrinfo hints = { 0 }, *servinfo, *p; 

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo: " << gai_strerror(rv) << '\n';
        return 1;
    }

    // socket 
    // connect
    for (p = servinfo; p; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cerr << "socket\n";
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            std::cerr << "connect\n";
            continue;
        }

        break;
    }
    
    if (!p) {
        std::cerr << "client: failed to connect\n";
        return 2;
    }

    freeaddrinfo(servinfo);

    // send 
    std::string msg = "u very sus la";
    if (write(sockfd, msg.c_str(), msg.size()) < 0) {
        std::cerr << "write\n";
        return -1;
    }

    // recv 
    std::string response;
    char buff[ 513 ] = { 0 };
    int r = 0;
    
    do {
        r = read(sockfd, buff, 512);
        if (r < 0) {
            std::cerr << "read\n";
            return -1;
        }
        buff[r] = 0;
        response += buff;
    } while (r == 512);

    std::cout << response << '\n';

    // close 
    close(sockfd);

    return 0;
}
