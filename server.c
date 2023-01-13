#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    int scket = socket(AF_INET, SOCK_STREAM, 0);
        if (scket == -1) {
            printf("ERROR | %s\n", strerror(errno));
        }
        else {
             printf("Socket Basariyla Olusturuldu!\n");
        }
         struct sockaddr_in sockadd;
            sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockadd.sin_family = AF_INET;
            sockadd.sin_port = htons(4800);
                // 127.0.0.1:4000
            int bnd = bind(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                if (bnd == -1) {
                    printf("ERROR | Bind Islemi Basarisiz!\n");
                }
                else {
                    printf("0x0 | Bind Islemi Basarili!\n");
                }
            int lstn = listen(scket, 1);
                if (lstn == -1) {
                    printf("ERROR | Dinleme Basarisiz!\n");
                }
                else {
                    printf("0x1 --> Port Dinleniyor! Port: %d\n", ntohs(sockadd.sin_port));
                }
                    struct sockaddr_in client;
                    socklen_t clientLen = sizeof(client);
                        int cAccept = accept(scket, (struct sockaddr*)&client, &clientLen);
                            if (cAccept == -1) {
                                printf("ERROR | Istek Kabul Edilemedi!\n");
                            }
                            else {
                                printf("0x2 --> Istek Basariyla Kabul Edildi!\n");
                            }
                            char clMessage[1024];
                            memset(clMessage, '\0', strlen(clMessage));
                                int r = recv(cAccept, clMessage, sizeof(clMessage), 0);
                                    if (r == -1) {
                                        printf("ERROR | Mesaj Alinamadi!\n");
                                    }
                                    else {
                                        printf("0x3 --> Mesaj Basariyla Alindi! Mesaj: %s\n", clMessage);
                                    }
                            close(cAccept);
                            close(scket);
}