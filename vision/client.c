/*
 * GC monitor client using UDP protocol.
 */
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include	"inet.h"
#include        "packets.h"
#include "open_sockets.h"

/* Does nothing much yet - takes the packet type on stdin, and fills the
   packet with garbage to send to the client.  If the sent packet is not 
   echoed back right away, there is an error message. */

void main(argc, argv)
int	argc;
char	*argv[];
{
  int	             sockfd;       /* socket file descriptor */
  struct sockaddr_in serv_addr;    /* socket address to server */
  char	sendline[MAXLINE];
  int whichpack;                   /* which packet ID to send */
  int	n;                         /* size of buffer */

  static int sequence = 0;

  struct track_packet track;

/* Set up sockets */

  if (open_clientside_socket(&sockfd,&serv_addr)) {
    fprintf(stderr,"Can't open socket\n");
    exit(1);
  }

/* get which packet to send from stdin */

  int MAXLOOP = 10;
  int i = 0;
  while (i<MAXLOOP) {
    i++;
    whichpack = PID_TRACK; // only one packet type right now

/* fill the sendline buffer with the appropriate packet */

    switch (whichpack) {
    case PID_TRACK:
      memset(&track,0,sizeof(track));
      track.packet_id = whichpack;
      track.sequence = sequence++;
      track.region_id = 1;
      track.range = 42.1;
      track.x = 56;
      track.y = 90;
      track.aspect_ratio = 4.0/3.0;
      n = pack_track(sendline,&track);

      break;
    default:
      fprintf(stderr,"Unknown packet type %d\n",whichpack);
      exit(-1);
    }

/* send packet to the server */

    send_packet(sockfd, &serv_addr, sendline, n);
    printf("sending packet of id %d and length %d\n",whichpack,n);

    sleep(1);
  }
/* bail */

  close(sockfd);
  exit(0);
}
