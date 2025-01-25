#include <winsock2.h>
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
    target.sin_port = htons(8080);
    target.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(buffer, 'A', sizeof(buffer));
    for (int i = 0; i < 550000; i++) {
        sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&target, sizeof(target));
        std::cout << "Sent packet to " << target.sin_addr.s_addr << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
