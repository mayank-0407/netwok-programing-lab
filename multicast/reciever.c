#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

int main(){

    int sockfd;
    struct sockaddr_in multicastaddr;
    struct ip_mreq multicastreq;

    char buffer[100];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&multicastaddr, sizeof(multicastaddr));
    multicastaddr.sin_family = AF_INET;
    multicastaddr.sin_port = htons(6000);
    multicastaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    multicastreq.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
    multicastreq.imr_interface.s_addr = inet_addr("10.0.2.15");

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bind(sockfd, (struct sockaddr*)&multicastaddr, sizeof(multicastaddr));

    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastreq, sizeof(multicastreq));

    socklen_t len = sizeof(multicastaddr);

    while(true){
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&multicastaddr, &len);
        printf("Message: %s\n", buffer);
    }
}
