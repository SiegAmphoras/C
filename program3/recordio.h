#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#ifndef _recordio_h
#define _recordio_h
#endif

int rio_open(const char *pathname, int flags, mode_t mode);

void * rio_read(int fd, int * return_value);

int rio_write(int fd, const void *buf, int count);

int rio_lseek(int fd, int offset, int whence);

int rio_close(int fd);
