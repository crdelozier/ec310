#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 1946
#define MAXLINE 1024

int main(){
  int sockfd;
  char buffer[MAXLINE];
  struct sockaddr_in servaddr;
  
  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
     perror("socket creation");
     exit(0);
  }

  strcpy(buffer,"test\n");
  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  
  int n, len, c;
  char ip_address[50];

  printf("Enter an IP address to send a message to: ");

  fgets(ip_address,50,stdin);
  for(c = 0; c < 50; c++){
    if(ip_address[c] == '\n'){
      ip_address[c] = '\0';
      break;
    }
  }
  
  if(inet_pton(AF_INET, ip_address, &servaddr.sin_addr) == 0){
    perror("IP Address: ");
    exit(0);
  }

  printf("Enter a message to send: ");

  fgets(buffer,100,stdin);

  sendto(sockfd, (const char*)buffer, strlen(buffer),
        MSG_CONFIRM, (const struct sockaddr*)&servaddr,
        sizeof(servaddr));
  close(sockfd);

  printf("Sent message!\n");

  return 0;
}
