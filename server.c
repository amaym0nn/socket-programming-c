#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main() {
    int sck;
        sck = socket(AF_INET, SOCK_STREAM, 0);
            if (sck < 0) { // if sck == -1 
                printf("ERROR | %s\n", strerror(errno));
            }
            else {
               printf("SUCCESSFUL | Socket Basariyla Olusturuldu!\n");
            }
            struct sockaddr_in sockadd, clientadd;
            socklen_t sockLen = sizeof(sockadd);
            socklen_t clientLen = sizeof(clientadd);
                sockadd.sin_addr.s_addr = inet_addr("127.0.0.1"); // local ip 
                sockadd.sin_family = AF_INET;   // TCP 
                sockadd.sin_port = htons(4000); // port --> 4000
            int bnd = bind(sck, (struct sockaddr*)&sockadd, sockLen);
                if (bnd < 0) {
                    printf("ERROR | %s\n", strerror(errno));
                }
                else {
                    printf("SUCCESSFUL | Bind Etme Basarili!\n");
                }
                int lstn = listen(sck, 1);
                if (lstn < 0) {
                    printf("ERROR | %s\n", strerror(errno));
                }
                else {
                    printf("SUCCESSFUL | Server Dinleniyor!\n");
                }
                 int acceptClient = accept(sck, (struct sockaddr*)&clientadd, &clientLen);
                    if (acceptClient < 0) {
                        printf("ERROR | %s\n", strerror(errno));
                    }   
                    else {
                        printf("SUCCESSFUL | Istek Basariyla Kabul Edildi!\n");
                    }
                    char clMessage[1024];
                    memset(clMessage, '\0', sizeof(clMessage)); // --> clientten gelen mesaj icin yer ayrildi
                    int rcv;
                        rcv = recv(acceptClient, clMessage, sizeof(clMessage), 0);
                            if (rcv < 0) {
                                printf("ERROR | %s\n", strerror(errno));
                            }
                            else {
                                printf("SUCCESSFUL | Clientten Gelen Mesaj: %s\n", clMessage);
                            }
                            char svMessage[] = "Isteginiz Server Tarafindan Alindi!\n";
                                int snd = send(acceptClient, svMessage, strlen(svMessage), 0);
                                    if (snd < 0) {
                                        printf("ERROR | %s\n", strerror(errno));
                                    }
                                    else {
                                        printf("SUCCESSFUL | Mesaj Basariyla Gonderildi!\n");
                                    }
            close(acceptClient);
            close(sck);
            return EXIT_SUCCESS;
}                   
