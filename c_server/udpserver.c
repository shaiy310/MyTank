/*
 * udpserver.c - A simple UDP echo server
 * usage: udpserver <port>
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include "runner.h"

#define BUFSIZE (16)

int main(int argc, char **argv)
{
	int sockfd;		/* socket */
	int portno;		/* port to listen on */
	int clientlen;		/* byte size of client's address */
	struct sockaddr_in serveraddr;	/* server's addr */
	struct sockaddr_in clientaddr;	/* client addr */
	struct hostent *hostp;	/* client host info */
	char *buf;		/* message buf */
	char *hostaddrp;	/* dotted decimal host addr string */
	int optval;		/* flag value for setsockopt */
	int n;			/* message byte size */
    pid_t pid = -1;

	/*
	 * check command line arguments
	 */
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	portno = atoi(argv[1]);

	/*
	 * socket: create the parent socket
	 */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("ERROR opening socket");
        return -1;
    }

	/* setsockopt: Handy debugging trick that lets
	 * us rerun the server immediately after we kill it;
	 * otherwise we have to wait about 20 secs.
	 * Eliminates "ERROR on binding: Address already in use" error.
	 */
	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
		   (const void *)&optval, sizeof(int));

	/*
	 * build the server's Internet address
	 */
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serveraddr.sin_addr.s_addr = 0x7F000001;
	serveraddr.sin_port = htons((unsigned short)portno);

	/*
	 * bind: associate the parent socket with a port
	 */
	if (bind(sockfd, (struct sockaddr *)&serveraddr,
		 sizeof(serveraddr)) < 0) {
		printf("ERROR on binding");
        return -1;
    }

	/*
	 * main loop: wait for a datagram, then echo it
	 */
	clientlen = sizeof(clientaddr);
    printf("starting loop\n");
	while (1) {

		/*
		 * recvfrom: receive a UDP datagram from a client
		 */
		buf = malloc(BUFSIZE);
		n = recvfrom(sockfd, buf, BUFSIZE, 0,
            (struct sockaddr *)&clientaddr, &clientlen);
		if (n < 0) {
			printf("ERROR in recvfrom");
        }

		/*
		 * gethostbyaddr: determine who sent the datagram
		 */
		hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
            sizeof(clientaddr.sin_addr.s_addr),
            AF_INET);
		if (hostp == NULL) {
			printf("ERROR on gethostbyaddr");
        }
		hostaddrp = inet_ntoa(clientaddr.sin_addr);
		if (hostaddrp == NULL) {
			printf("ERROR on inet_ntoa\n");
        }

		/*
		 * sendto: echo the input back to the client
		 */
		//n = sendto(sockfd, buf, n, 0,
        //    (struct sockaddr *)&clientaddr, clientlen);
		//if (n < 0)
		//	printf("ERROR in sendto");
        //printf("server received %d bytes\n", n);
        switch (buf[0]) {
            case '0':
                // stop python
                if (pid != -1) {
                    kill(pid, SIGKILL);
                    pid = -1;
                }
                break;
            case '1':
                // run python and wait to finish
                pid = start_process(true);
                printf("process ended.\n");
                break;
            case '2':
                // run python and continue
                pid = start_process(false);
                printf("process skipped.\n");
                break;
        }
	}
}
