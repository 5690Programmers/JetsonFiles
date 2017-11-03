#define PID_TRACK  1            /* defines for packet ID */
#define PID_CHECK  2

/* This packet is what gets sent to the RIO with tracking data */
struct track_packet {           /* packet_id = 1 */
  unsigned short packet_id;     /* What type of packet? */  
  unsigned int sequence;       /* Counter to allow send/receive checks */
  int time;						/*Timestamp of frame*/
  int range;                  /* How far to tape */
  unsigned short x1;                      /* x-coordinate of centroid */
  unsigned short x2;						/* second contour x value*/
};

/* prototypes for packets functions */

void send_packet(int,struct sockaddr_in *,char *, int);
int pack_track(char *, struct track_packet *);
int get_packet(int, struct sockaddr_in *, char *);
void handle_track(char *, int, struct track_packet *);

// size of temporary strings
#define MAXLINE 512
// we can't get floats across a socket.  We can, however, multiply 
// them by something, call it an int, then divide it by something 
// later on to get it back
#define FLOAT_SCALE_INT 10000
#define FLOAT_SCALE_FLOAT 10000.0
