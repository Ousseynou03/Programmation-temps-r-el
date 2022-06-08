#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc, char *argv[])
{
int serv_sock;
int clnt_sock;
char op1[50];
char op2[50];

struct sockaddr_in serv_addr;
struct sockaddr_in clnt_addr;
socklen_t clnt_addr_size;

char message1[]="rebonjour";
char message[30];
char messagee[30];



serv_sock=socket(PF_INET, SOCK_STREAM, 0);


memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(9001);

bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
listen(serv_sock,5);

clnt_addr_size=sizeof(clnt_addr);  
clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
read(clnt_sock,message,sizeof(message)-1);
printf("Message from client: %s \n", message);
scanf("%s",op1);
//write(clnt_sock, message1, sizeof(message1));
write(clnt_sock, op1, sizeof(op1));


read(clnt_sock,messagee,sizeof(messagee)-1);
printf("Message from client: %s \n", messagee);
scanf("%s",op2);
//write(clnt_sock, message1, sizeof(message1));
write(clnt_sock, op2, sizeof(op2));

close(clnt_sock);
close(serv_sock);
return 0;
}