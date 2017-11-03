#include        <string.h>
#include	"inet.h"
#include        "open_sockets.h"

int open_clientside_socket(sockfd, serv_addr)
     int                *sockfd;    /* server socket file descriptor */
     struct sockaddr_in *serv_addr; /* server socket address */
{
  struct sockaddr_in	cli_addr;   /* socket for the client to listen on */
  int flag_on  = 1;
  int flag_off = 0;

  /*
   * Fill in the structure "serv_addr" with the address of the
   * server that we want to send to.
   */

  memset((char *) serv_addr, 0, sizeof(*serv_addr));
  serv_addr->sin_family      = AF_INET;
  serv_addr->sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  serv_addr->sin_port        = htons(SERV_UDP_PORT);

  /*
   * Open a UDP socket (an Internet datagram socket).
   */

  if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    fprintf(stderr,"client: can't open datagram socket\n");
    return(-1);
  }

  /*
   * Bind a local address for the client to listen on.
   */
  
  memset((char *) &cli_addr, 0, sizeof(cli_addr));	/* zero out */
  cli_addr.sin_family      = AF_INET;
  cli_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  cli_addr.sin_port        = htons(CLI_UDP_PORT);
  if (bind(*sockfd, (struct sockaddr *) &cli_addr, sizeof(cli_addr)) < 0) {
    fprintf(stderr,"client: can't bind local address\n");
    return(-1);
  }

/* make this socket non-blocking, so we can retry if packets get lost */
  if (ioctl(*sockfd,FIONBIO,&flag_on) < 0)
    fprintf(stderr,"FIONBIO error - can't set non-blocking flag on socket\n");
  return(0);
}


/* This routine opens up the socket needed to listen for the client */

int open_serverside_socket(sockfd)
     int *sockfd;                    /* socket file descriptor opened */
{
  struct sockaddr_in sock_addr;      /* the socket address */

  /*
   * Open a UDP socket (an Internet datagram socket).
   */

  if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    fprintf(stderr,"server: can't open datagram socket");
    return(-1);
  }

  /*
   * Bind our local address so that the client can send to us.
   */

  memset((char *) &sock_addr, 0, sizeof(sock_addr));
  sock_addr.sin_family      = AF_INET;
  sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  sock_addr.sin_port        = htons(SERV_UDP_PORT);
  
  if (bind(*sockfd, 
	   (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0) {
    fprintf(stderr,"server: can't bind local address\n");
    return(-1);
  }
  
  return(0);
}
