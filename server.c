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
            sockadd.sin_port = htons(4500);
                // 127.0.0.1:4500
            
            // Bind İşlemi 
            int bnd = bind(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                if (bnd == -1) {
                    printf("ERROR | Bind İşlemi Başarısız!\n");
                }
                else {
                    printf("SUCCESSFUL | Bind İşlemi Başarılı!\n");
                }
            // Port Dinlemesi
            int lstn = listen(scket, 1);
                if (lstn == -1) {
                    printf("ERROR | Port Dinleme Başarısız!!\n");
                }
                else {
                    printf("SUCCESSFUL | Port Başarıyla Dinleniyor! Port: %d\n", ntohs(sockadd.sin_port));
                }
                    // Buradan itibaren Client kodlaması yapılacaktır. Amaç, client'tan gelecek mesajı alıp ekrana bastırmak.
                    struct sockaddr_in client;
                    socklen_t clientLen = sizeof(client);
                        // Client'tan gelen isteği kabul et
                        int cAccept = accept(scket, (struct sockaddr*)&client, &clientLen);
                            if (cAccept == -1) {
                                printf("ERROR | İstek Kabul Edilemedi!\n");
                            }
                            else {
                                printf("SUCCESSFUL | İstek Kabul Edildi!\n");
                            }
                            // Client'tan gelecek mesaj için yer ayır
                            char clMessage[1024];
                            memset(clMessage, '\0', strlen(clMessage));
                                int r = recv(cAccept, clMessage, sizeof(clMessage), 0);
                                    if (r == -1) {
                                        printf("ERROR | Mesaj Alınamadı!\n");
                                    }
                                    else {
                                        printf("SUCCESSFUL | Mesaj Başarıyla Alındı! Mesaj: %s\n", clMessage);
                                    }
                            close(cAccept);
                            close(scket);
}