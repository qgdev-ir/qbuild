#include "qson.h"

bool qson_is_white_space(char chr) {
	int array_length = sizeof(QSON_WHITESPACES) / sizeof(QSON_WHITESPACES[0]);
	for (int i = 0; i < array_length; i++) {
		if (chr == QSON_WHITESPACES[i]) return true;
	}
	return false;
}

void qson_skip_white_spaces(char *buffer, int *index) {
	while (qson_is_white_space(buffer[*index])) (*index)++;
}

