/*
 * Definitions for TCP and UDP client/server programs.
 */

#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>

#define	SERV_UDP_PORT   5800
#define	SERV_TCP_PORT	5800
#define	CLI_UDP_PORT	5801
#define	CLI_TCP_PORT	5802
/* #define	SERV_HOST_ADDR	"128.197.43.133" 	 host addr for server */
#define	SERV_HOST_ADDR	"10.56.90.2"	/* host addr for server  #define	SERV_HOST_ADDR	"10.56.90.63" */
/* #define      SERV_HOST_ADDR  "131.215.124.102"  host addr for server */

extern char     *pname;
