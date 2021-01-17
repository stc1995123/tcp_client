#include<sys/socket.h>
#include <string.h>
#include<netinet/in.h>
#include <unistd.h>
#include<assert.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

// A Client app; send message and close;
//set server address -> create socket -> connect -> send() -> close();
int main(int argc ,char* argv[]){ 
        // usage: connect to a port and send message; 
        //    ./Client1 127.0.0.1 12345 hhhfff
    if(argc<3){
        printf("\n parameter: ip, port, message\n") ;
        return 0;
    }
    // set object server address;
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server_add;
    bzero(&server_add,sizeof(server_add));
    server_add.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&server_add.sin_addr);
    server_add.sin_port = htons(port);

    // create socket;
    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd>=0);

    // connect() and verify;
    if( connect(sockfd,(sockaddr* )&server_add,sizeof(server_add)) == -1){
        printf("connect failed\n ");
        return 0;
    }
    else{

    //  send message : send(); // 发送一条消息就关闭
    const char *message = argv[3];
    send(sockfd, message, strlen(message)+1, MSG_OOB);

    //  recv message
        // char recv_buffer[1024];
        // memset(recv_buffer, 0, 1024);
        // int recv_err = recv(sockfd, recv_buffer, 1023, 0);
        // printf("%s\n", recv_buffer);
        // close(sockfd);
        // return 0;
    }  
    // close();
        //sleep(10);
    close(sockfd);
    return 0;




}