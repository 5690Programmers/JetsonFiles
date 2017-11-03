#include        <unistd.h>
#include        <string.h>
#include		"inet.h"
#include        "packets.h"

void send_packet(sockfd, pserv_addr, buffer, buffsiz)
     int		sockfd;         /* socket FD to send to */
     struct sockaddr_in	*pserv_addr;	/* ptr to sockaddr_in structure */
     char               *buffer;        /* the data to send */
     int                buffsiz;        /* how much data to send */
{
  char	sendline[MAXLINE], recvline[MAXLINE + 1];
  int   n;

/* copy the data to be sent */

  memcpy(sendline,buffer,buffsiz);

/* Send the buffer */

  if (sendto(sockfd, sendline, buffsiz, 0, (struct sockaddr *) pserv_addr, 
	     sizeof(*pserv_addr)) != buffsiz)
    fprintf(stderr,"dg_cli: sendto error on socket\n");
  
  return;
}

/*
 * This routine fills a track packet with data, and copies that data
   into the space at outbuffer.  The size of the output buffer is returned.
 */
int pack_track(outbuffer,outpacket)
     char *outbuffer;               /* buffer to be filled */
     struct track_packet *outpacket;/* the data packet */
{
  int buffsize;                     /* size of the buffer */

/* Fill packet to send */

/* convert to network byte order */

  outpacket->packet_id = htons(outpacket->packet_id);
  outpacket->sequence = htonl(outpacket->sequence);
  outpacket->region_id = htons(outpacket->region_id);
  outpacket->range = htonl(outpacket->range*FLOAT_SCALE_FLOAT);
  outpacket->x1 = htons(outpacket->x1);
  outpacket->x2 = htons(outpacket->x2);
  outpacket->aspect_ratio = htonl(outpacket->aspect_ratio*FLOAT_SCALE_FLOAT);
  outpacket->time = htonl(outpacket->time);

/* pack send info into the buffer */

  buffsize = sizeof(*outpacket);
  memcpy(outbuffer,outpacket,buffsize);
  return(buffsize);
}


int get_packet(sockfd, pcli_addr, mesg)
     int		sockfd;         /* the socket to listen on */
     struct sockaddr_in	*pcli_addr;	/* ptr to client sockaddr structure */
     char	        *mesg;          /* input buffer */
{
  int	       n, clilen;


/* read a buffer from the socket */

  clilen = sizeof(*pcli_addr);
  n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *)pcli_addr, 
	       &clilen);
  if (n < 0)
    fprintf(stderr,"dg_echo: recvfrom error");
  mesg[n] = 0;           /* null terminate */
  printf("From %s:\n",inet_ntoa(pcli_addr->sin_addr));
  return(n);
}

/* This routine deals with a track packet */

void handle_track(inbuffer, n, inpacket)
     char *inbuffer;              /* the input buffer */
     int n;                       /* the size of that buffer */
     struct track_packet *inpacket;/* a track packet */
{

/* Check that the packet size is correct, and fill the structure if it is */

  if (n != sizeof(*inpacket)) {
    fprintf(stderr,"Whoa!  %d is wrong packet size for this type (%d)\n",
	    n,sizeof(*inpacket));
    return;
  } else {
    memcpy(inpacket,inbuffer,n);
  }

/* Convert to local byte order */

  inpacket->packet_id = ntohs(inpacket->packet_id);
  inpacket->sequence = ntohl(inpacket->sequence);
  inpacket->region_id = ntohs(inpacket->region_id);
  inpacket->range = (float)ntohl(inpacket->range)/FLOAT_SCALE_FLOAT;
  inpacket->x1 = ntohs(inpacket->x1);
  inpacket->x2 = ntons(inpacket->x2);
  inpacket->aspect_ratio = (float)ntohl(inpacket->aspect_ratio)/FLOAT_SCALE_FLOAT;
  inpacket->time = ntohl(inpacket->time);


}
