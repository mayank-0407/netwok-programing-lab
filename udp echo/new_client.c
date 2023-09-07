#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc,char **argv)
{
 int sockfd,n;
 char sendline[100];
 char recvline[100];
 struct sockaddr_in servaddr;
 sockfd=socket(AF_INET,2,0);
 bzero(&servaddr,sizeof servaddr);
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(22000);
 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
 //inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 int my_input;
 
 while(1)
 {
 int len = sizeof(servaddr);
 bzero( sendline, 100);
 bzero( recvline, 100);
 fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
 sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *) &servaddr,len);
 recvfrom(sockfd,recvline,sizeof(recvline),0,(struct sockaddr *) &servaddr,&len);
 printf("%s",recvline);
 }
}