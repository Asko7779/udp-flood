#include <winsock2.h>    // (windows compatible only)
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in target;
    char buffer[65507];

    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    target.sin_family = AF_INET;

    // target port and IP, can be adjusted
    
    target.sin_port = htons(8080);                      
    target.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    memset(buffer, 'A', sizeof(buffer));    // fill up the packet
    for (int i = 0; i < 100; i++) {         // sends 100 packets, also adjustable
        sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&target, sizeof(target));
        std::cout << "Sent packet to " << target.sin_addr.s_addr << std::endl;
    }

    // socket clearing
    closesocket(sock);
    WSACleanup();
    return 0;
}
