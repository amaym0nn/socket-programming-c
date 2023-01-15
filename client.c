#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main() {
        int scket = socket(AF_INET, SOCK_STREAM, 0);
        if (scket == -1) {
            printf("ERROR | Failed to Create Socket\n");
        }
        else {
             printf("SUCCESSFUL | Socket Created!\n");
        }
         struct sockaddr_in sockadd;
            sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockadd.sin_family = AF_INET;
            sockadd.sin_port = htons(4500);
                // Make Connection
                int cnt = connect(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                    if (cnt == -1) {
                        printf("ERROR | Connection Failed...!\n");
                    }
                    else {
                        printf("SUCCESSFUL | Connection Successful!\n");
                    }
                    // Get an input to send a message to the server.
                    char svMessage[1024];
                        printf("Enter Message: ");
                        fgets(svMessage, 1024, stdin);
                            // Send received Message to Server.
                            int snd = send(scket, svMessage, strlen(svMessage), 0);
                                if (snd == -1) {
                                    printf("ERROR | Message could not be Sent!\n");
                                }
                                else {
                                    printf("SUCCESSFUL | Message Sent!\n");
                                }
}