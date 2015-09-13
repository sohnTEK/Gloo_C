#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "connect.h"

struct GlooHandler *gloo_connect(char *ip, int port) {
	int sockfd = 0;

	struct sockaddr_in servAddr;
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "ERROR: Could not create socket\n");
		return NULL;
	}

	memset(&servAddr, '0', sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	if(inet_pton(AF_INET, ip, &servAddr.sin_addr) <= 0) {
		fprintf(stderr, "ERROR: inet_pton error occured\n");
		return NULL;
	}

	if(connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		fprintf(stderr, "ERROR: Connection failed\n");
		return NULL;
	}

	struct GlooHandler *gh = malloc(sizeof(struct GlooHandler));
	gh->sockfd = sockfd;
	return gh;
}
