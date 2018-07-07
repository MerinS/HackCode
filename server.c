#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    int listener = 0;
    int ret;
    struct sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        printf("%s\n", "Unable to open listener");
        return -1;
    }

    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);

    bind(listener, (struct sockaddr*)&addr, sizeof(addr));
    ret = listen(listener, 10);
    if (ret) {
        printf("%s\n", "Listen error");
        return -1;
    }
    printf("%s\n", "Listening...");

    while (1) {
        int sock = accept(listener, NULL, NULL);
        if (sock < 0) {
            printf("%s\n", "Unable to accept connection");
            return -1;
        }
        printf("%s\n", "Accepted connection");

        int fd  = open("srv-status.log", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
        size_t size;
        read(sock, &size, sizeof(size));
        void *data = malloc(size);
        read(sock, data, size);
        char buf[100];
        sprintf(buf, "Reading: %f Timestamp: %lu\n", *((float *)data), time(0));
        write(fd, buf, strlen(buf));
        close(fd);
        free(data);
    }
    return 0;
}
