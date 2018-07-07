#include <errno.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <FallDetector.h>



int main()
{
    char *portname = "/dev/tty96B0";
    int fd;
    int wlen;

    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }


    while (1){
        char buf[80];
        int rdlen;
        char* pos;
        float read[3];
        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            char* pch  = strtok_r(&buf,",", &pos);
            int i = 0;
            while (pch!= NULL){
                read[i] = atof(pch);
                pch = strtok_r(NULL, ",", &pos);
                ++i;
            }
            run_fall_detector(read[0],read[1],read[2]);
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
    } 
}