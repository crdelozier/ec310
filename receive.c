#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>

#define SERVER_PORT 1946

struct sockaddr_in serv;
int fd;
int conn;
char message[100] = "";

int main(){
  serv.sin_family = AF_INET;
  serv.sin_port = htons(SERVER_PORT);
  serv.sin_addr.s_addr = INADDR_ANY;
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  bind(fd, (struct sockaddr *)&serv, sizeof(serv));
  listen(fd,5);
  while(conn = accept(fd, (struct sockaddr *)NULL, NULL)) {
    int pid;
    if((pid = fork()) == 0) {
      while (recv(conn, message, 100, 0)>0) {
        printf("Message Received: %s", message);
        memset(message,0,sizeof(message));
      }
      exit(0);
    }
  }
}
