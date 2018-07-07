#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <time.h>

int write_out(char *s_name, void *data, size_t size) {
    int fd;
    int sock;
    struct sockaddr_in server_addr;

    fd  = open("status.log", O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
    char buf[100];
    sprintf(buf, "Reading: %f\tTimestamp: %lu\n", *((float *)data), time(0));
    write(fd, buf, strlen(buf));
    close(fd);

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("Socket Failure\n");
            return -1;
    }

    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8000);

    if(inet_pton(PF_INET, s_name, &server_addr.sin_addr) <= 0) {
        printf("%s\n", "Connection error");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
           printf("Connection Failed\n");
           return -1;
    }
    printf("%s\n", "Connected");

    write(sock, &size, sizeof(size));
    write(sock, data, size);
    return 0;
}
