#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



int main(int argc, char* argv[])
{
int sock;
struct sockaddr_in serv_addr;
char message1[50]="Bonjour entrez une operande";
char message2[50]="Bonjour entrez la deuxieme operande";
int str_len;
char ops[50];
char ops1[50];


sock=socket(PF_INET, SOCK_STREAM, 0);


memset(&serv_addr, 0, sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
serv_addr.sin_port=htons(9001);

connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
write(sock,message1,sizeof(message1));
//read(sock, message1, sizeof(message1)-1);
read(sock, &ops, sizeof(&ops));
printf("Message from server: %s\n", ops);  


write(sock,message2,sizeof(message2));
read(sock, ops1, sizeof(ops1)-1);
printf("Message from server: %s\n", ops1);
close(sock);
return 0;
}