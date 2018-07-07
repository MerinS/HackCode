#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "FallDetector.h"
#include "write_out.h"


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <Server IP>\n", argv[0]);
        return -1;
    }

    char *portname = "/dev/tty96B0";
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }

    char * buf;
    buf  = (char *)malloc(80*sizeof(char));
    while (1){
        int rdlen;
        char* pos;
        float read_list[3];
        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            char* pch  = strtok_r(buf,",", &pos);
            int i = 0;
            while (pch!= NULL){
                read_list[i] = atof(pch);
                pch = strtok_r(NULL, ",", &pos);
                ++i;
            }
            int return_val = run_fall_detector(read_list[0],read_list[1],read_list[2]);
            if(return_val == 1){
                //Detected a fall
                printf("Fall Detected\n");
                write_out(argv[1], read_list, sizeof(read_list));
            }
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
    }
}
