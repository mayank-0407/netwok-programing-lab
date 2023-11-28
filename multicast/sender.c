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
    char buffer[100];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&multicastaddr, sizeof(multicastaddr));
    multicastaddr.sin_family = AF_INET;
    multicastaddr.sin_port = htons(6000);
    multicastaddr.sin_addr.s_addr = inet_addr("225.1.1.1");

    int opt = 1;
    setsockopt(sockfd, IPPROTO_IP,IP_MULTICAST_LOOP, &opt, sizeof(opt));

    struct in_addr interface_addr;
    interface_addr.s_addr = inet_addr("10.0.2.15");
    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, &interface_addr, sizeof(interface_addr));

    socklen_t len = sizeof(multicastaddr);

    while(true){
        fgets(buffer, sizeof(buffer), stdin);
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&multicastaddr, len);
    }
}
