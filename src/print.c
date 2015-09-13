#include <jansson.h>
#include <string.h>
#include "print.h"

int gloo_print(struct GlooHandler *gh, char *data) {
	json_t *obj = json_object();
	json_t *_data = json_string(data);
	json_t *_action = json_integer(0);
	int err = 0;

	err = json_object_set_new(obj, "action", _action);
	if(err < 0) {
		return err;
	}

	err = json_object_set_new(obj, "data", _data);
	if(err < 0) {
		return err;
	}

	char *packet = json_dumps(obj, JSON_ENCODE_ANY);
	strcat(packet, "\n");
	int n = write(gh->sockfd, packet, strlen(packet));
	if(n < 0) {
		fprintf(stderr, "ERROR: Could not write to socket");
		return 1000;
	}

	char buffer[1];
	bzero(buffer, 1);
	n = read(gh->sockfd, buffer, 0);
	if(n < 0) {
		fprintf(stderr, "ERROR: Could not get response");
		return 2000;
	}

	free(packet);
	free(json_object_get(obj, "action"));
	free(json_object_get(obj, "data"));
	free(obj);
	return buffer[0];
}
