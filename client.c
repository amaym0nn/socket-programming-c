#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main() {
        int scket = socket(AF_INET, SOCK_STREAM, 0);
        if (scket == -1) {
            printf("ERROR | Socket Oluşturulamadı!", strerror(errno));
        }
        else {
             printf("SUCCESSFUL | Socket Başarıyla Oluşturuldu!\n");
        }
         struct sockaddr_in sockadd;
            sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockadd.sin_family = AF_INET;
            sockadd.sin_port = htons(4500);
                // Bağlantıyı Gerçekleştir
                int cnt = connect(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                    if (cnt == -1) {
                        printf("ERROR | Bağlantı Başarısız Oldu!\n");
                    }
                    else {
                        printf("SUCCESSFUL | Bağlantı Başarılı!\n");
                    }
                    // Server'a Mesaj göndermek için input al.
                    char svMessage[1024];
                        printf("Mesaj Giriniz: ");
                        fgets(svMessage, 1024, stdin);
                            // Server'a alınan mesajı gönder.
                            int snd = send(scket, svMessage, strlen(svMessage), 0);
                                if (snd == -1) {
                                    printf("ERROR | Mesaj Gönderilemedi!\n");
                                }
                                else {
                                    printf("SUCCESSFUL | Mesaj Gönderildi!\n");
                                }
}