#ifndef __GLOO_CONNECT_H
#define __GLOO_CONNECT_H
struct GlooHandler {
	int sockfd;
};

struct GlooHandler *gloo_connect(char *ip, int port);
#endif
