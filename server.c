#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    int scket = socket(AF_INET, SOCK_STREAM, 0);
        if (scket == -1) {
            printf("ERROR | Failed to Create Socket!");
        }
        else {
             printf("SUCCESSFUL | Socket Created!\n");
        }
         struct sockaddr_in sockadd;
            sockadd.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockadd.sin_family = AF_INET;
            sockadd.sin_port = htons(4500);
                // 127.0.0.1:4500
            
            // Bind İşlemi 
            int bnd = bind(scket, (struct sockaddr*)&sockadd, sizeof(sockadd));
                if (bnd == -1) {
                    printf("ERROR | Binding Failed...!\n");
                }
                else {
                    printf("SUCCESSFUL | Binding Successful!\n");
                }
            // Port Dinlemesi
            int lstn = listen(scket, 1);
                if (lstn == -1) {
                    printf("ERROR | Port Listening Failed...!\n");
                }
                else {
                    printf("SUCCESSFUL | Port Listening Successful! Port: %d\n", ntohs(sockadd.sin_port));
                }
                    /*
                        Client coding will be done from here. The aim is to receive the message from the client and print it on the screen.
                    */
                    struct sockaddr_in client;
                    socklen_t clientLen = sizeof(client);
                        // Accept the request from the client
                        int cAccept = accept(scket, (struct sockaddr*)&client, &clientLen);
                            if (cAccept == -1) {
                                printf("ERROR | Request not Accepted!\n");
                            }
                            else {
                                printf("SUCCESSFUL | The Request has been successfully Accepted!\n");
                            }
                            // Reserve space for message from client
                            char clMessage[1024];
                            memset(clMessage, '\0', strlen(clMessage));
                                int r = recv(cAccept, clMessage, sizeof(clMessage), 0);
                                    if (r == -1) {
                                        printf("ERROR | Message not Received!\n");
                                    }
                                    else {
                                        printf("SUCCESSFUL | Messsage Received. Message: %s\n", clMessage);
                                    }
                            close(cAccept);
                            close(scket);
}