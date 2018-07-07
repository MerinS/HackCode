#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "FallDetector.h"
#include "write_out.h"
#include <time.h>


FILE *f;

int main(int argc, char **argv)
{
    f = fopen("datalog", "w");
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
    buf  = (char *)malloc(sizeof(char));
    while (1){
        int rdlen;
        char* pos;
        //float read_list[3];
        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
            char* pch  = strtok_r(buf,",", &pos);
            int i = 0;
            float val;
            while (pch!= NULL){
                val = atof(pch)*9.8;
                pch = strtok_r(NULL, ",", &pos);
                ++i;
            }
            int return_val = run_fall_detector(val);
            //fprintf(f, "%f\n", val);
            if(return_val == 1){
                //Detected a fall
                printf("Fall Detected\n");
                write_out(argv[1], &val, sizeof(val));
            }
            printf("%s\n", buf);
        } else if (rdlen < 0) {
            printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }
    }
    fclose(f);
}
