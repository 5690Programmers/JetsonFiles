/*
 * Server stub for exercising GC monitor sockets.
 */
#include        <stdlib.h>
#include        <string.h>
#include	"inet.h"
#include        "packets.h"
#include "open_sockets.h" 

/* This routine does little yet.  It accepts GC data packets and prints them
   out.  Upon receiving a packet, it immediately echos it back for confirmation
   of the reciept. */
 
void main(argc, argv)
     int	argc;
     char	*argv[];
{
  int			sockfd;             /* listen socket file descriptor */
  struct sockaddr_in	cli_addr;           /* write-to-client socket address */
  char                  inbuffer[MAXLINE];  /* incoming data */
  unsigned short        packid = 0;         /* incoming packet ID */
  int                   n;                  /* packet length */

  struct track_packet   track;              /* a track packet */

/* Open socket to listen on for the client */

  if (open_serverside_socket(&sockfd)) {
    fprintf(stderr,"Can't open socket\n");
    exit(1);
  }

/* Go into the "receive and echo" routine */

  for ( ; ; ) { 
    n = get_packet(sockfd, &cli_addr, inbuffer);

    /* Find packet type */

    memcpy(&packid,inbuffer,sizeof(track.packet_id));
    packid = ntohs(packid);

/* deal with that packet */

    switch (packid) {
    case PID_TRACK:
      handle_track(inbuffer,n,&track);
      printf("packet_id : %d\n",track.packet_id); /* print packet to stdout */
      printf("sequence : %d\n",track.sequence); 
      printf("region_id : %d\n",track.region_id); 
      printf("range : %f\n",track.range); 
      printf("x : %d\n",track.x); 
      printf("y : %d\n",track.y); 
      printf("aspect_ratio : %f\n",track.aspect_ratio); 
      printf("\n");
      printf("time : %d\n"); //changes
      break;
    default:
      fprintf(stderr,"Unknown packet type %d and length %d\n",packid,n);
    }
  }

  /* NOTREACHED */
}
