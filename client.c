#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int sck = socket(AF_INET, SOCK_STREAM, 0);
        if (sck < 0 ) {
            printf("ERROR | %s\n", strerror(errno));
        }
        else {
            printf("SUCCESSFUl | Socket Basariyla Olusturuldu!\n");
        }
        struct sockaddr_in sockadd, clientadd;
            sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockadd.sin_port = htons(4000);
            sockadd.sin_family = AF_INET;
        socklen_t sockLen = sizeof(sockadd);
        socklen_t clientLen = sizeof(clientadd);
            int cnt = connect(sck, (struct sockaddr*)&sockadd, sockLen);
                if (cnt < 0) {
                    printf("ERROR | %s\n", strerror(errno));
                }
                else {
                    printf("SUCCESSFUL | Server'a Basariyla Baglanildi!\n");
                }
                char clMess[1024]; 
                    printf("Mesaj Giriniz: ");
                    fgets(clMess, 1024, stdin);
                    strtok(clMess, "\n");
                        int snd;
                            snd = send(sck, clMess, strlen(clMess), 0);
                            if (snd < 0) {
                                printf("ERROR | %s\n", strerror(errno));
                            }
                            else {
                                printf("SUCCESSFUL | Mesajiniz Server'a Gonderildi!\n");
                            }
                            char svMessage[1024];
                                memset(svMessage, '\0', strlen(svMessage));
                                int rcv = recv(sck, svMessage, sizeof(svMessage), 0);
                                    if (rcv < 0) {
                                        printf("ERROR | %s\n", strerror(errno));
                                    }
                                    else {
                                        printf("SUCCESSFUL | Mesaj Basariyla Alindi!\n");
                                    }
                                    return EXIT_SUCCESS;
}   