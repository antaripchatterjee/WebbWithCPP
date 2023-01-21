#include <aio.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main() {
    FILE* fp = fopen("./src/cppweb.cpp", "r");
    if(fp == NULL) return -1;
    int fd = fileno(fp);
    struct aiocb *aio = (struct aiocb*) malloc(sizeof(struct aiocb));
    char buffer[BUFSIZE+1] = { 0 };
    aio->aio_buf = buffer;
    aio->aio_fildes = fd;
    aio->aio_nbytes = BUFSIZE;
    aio->aio_offset = 0;
    while(1) {
        int res = aio_read(aio);
        if(res < 0) {
            free(aio);
            fclose(fp);
            return -2;
        }
        while(aio_error(aio) == EINPROGRESS);
        int ret = aio_return(aio);
        if(ret <= 0) {
            free(aio);
            fclose(fp);
            return -3;
        }
        printf("Got %d bytes\n", ret);
        printf("content \n\n%s\n", buffer);
        aio->aio_offset += BUFSIZE;
        memset(aio->aio_buf, 0, BUFSIZE+1);
    }
    free(aio);
    fclose(fp);
    return 0;
}