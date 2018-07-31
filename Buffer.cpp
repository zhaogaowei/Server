#include "Buffer.h"

size_t Buffer::readFd(const int fd) {
	char extrabuf[65535];
	char *p = extrabuf;
	int nleft = 65535;
	int nread;
	while ((nread = read(fd, p, static_cast<size_t>(nleft))) < 0) {
		if (errno == EINTR)
			nread = 0;
		else
			return 0;
	}
	append(extrabuf, nread);
	return nread;
}

void Buffer::sendFd(const int fd) {
	size_t bytesSent = 0;
	size_t bytesLeft = readableBytes();
	char *p = peek();
	while (bytesLeft)
	{
		if ((bytesSent = write(fd, p, bytesLeft)) < 0) {
			if (errno == EINTR)
				bytesSent = 0;
			else
				return;
		}
		bytesLeft -= bytesSent;
		p += bytesSent;
	}
	resetBuffer();
}