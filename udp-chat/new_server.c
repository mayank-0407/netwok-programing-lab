#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
 char str[100];
 char sendline[100];
 int listen_fd;
 struct sockaddr_in servaddr,claddr;
 listen_fd = socket(AF_INET, 2, 0);
 bzero( &servaddr, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(22000);
 bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 listen(listen_fd, 10);

 while(1)
 {
 int len = sizeof(claddr);
 bzero( sendline, 100);
 bzero( str, 100);
 recvfrom(listen_fd,str,sizeof(str),0,(struct sockaddr *) &claddr,&len);
 printf("Recieved from client  - %s",str);
 fgets(sendline,100,stdin);
 sendto(listen_fd,sendline,strlen(sendline),0,(struct sockaddr *) &claddr,len);
 if(strncmp("exit",sendline,4)==0)  {
 printf("Server Closed \n");
 close(listen_fd);
 break;
 }
 }
}