#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int write_out(char *s_name, void *data, size_t size) {
    int fd;
    int ret;
    struct sockaddr_in server_addr;

    fd  = open("status.log", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    ret = write(fd, data, size);
    if (ret != size) {
        return -ret;
    }
    close(fd);

    //server_addr.sin_family = AF_INET;
    //server_addr.sin_port = htons(5000);
    return 0;
}
