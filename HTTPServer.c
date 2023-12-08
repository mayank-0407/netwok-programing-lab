#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>

int main(){
    int listen_fd;
    sturct sockaddr_in addr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_famil=AF_INET;
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    addr.sin_port=htons(8080);

    bind(listen_fd,(struct sockaddr *)&addr,sizeof(addr));
    listen(listen_fd,10);

    int addrlen=sizeof(addr);
    while(1){
        int com_fd=accept(listen_fd,(struct sockaddr *)&addr,(struct socklen_t *)&addrlen);

        char recc[2000],buffer[2000]={};
        recc=read(com_fd,buffer,2000);
        print("%s",recc);

        char *response="HTTP/1.1 200 OK\r\n"
        write(com_fd,response,strlen(response));
        close(listen_fd);
    }
}
