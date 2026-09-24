#include <qbuild/qbuild.internal.h>
#include <stdarg.h>

void qbuild_string_lower(char *buf) {
	for (char *p = buf; *p; p++)
		if ('A' <= *p && *p <= 'Z')
			*p += 'a' - 'A';
}

char *qbuild_string_format(const char *fmt, ...) {
	va_list ap, ap2;
	va_start(ap, fmt);
	va_copy(ap2, ap);

	size_t len = vsnprintf(NULL, 0, fmt, ap) + 1;
	va_end(ap);

	char *buffer = malloc(len);
	if (!buffer) return NULL;

	int r = vsnprintf(buffer, len, fmt, ap2);
	va_end(ap);
	return buffer;
}

