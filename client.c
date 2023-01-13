#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

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
                int cnt = connect(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                    if (cnt == -1) {
                        printf("ERROR | Baglanti Basarisiz Oldu!\n");
                    }
                    else {
                        printf("0x0 --> Baglanti Basarili!\n");
                    }
                    char svMessage[1024];
                        printf("Mesaj Giriniz: ");
                        fgets(svMessage, 1024, stdin);
                            int snd = send(scket, svMessage, strlen(svMessage), 0);
                                if (snd == -1) {
                                    printf("ERROR | Mesaj Gonderilemedi!\n");
                                }
                                else {
                                    printf("0x1 --> Mesaj Gonderildi!\n");
                                }
}