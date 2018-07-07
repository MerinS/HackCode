CC = gcc
CFLAGS = -std=c11 -Wall -pthread

TARGET = write-out-test
SERVER = evil-server
DETECTOR = FallDetectorTest
M_SRC = write_out.c
S_SRC = server.c
D_SRC = FallDetector.c FallDetector.h

default: $(TARGET) $(SERVER)

$(TARGET): $(M_SRC)
	$(CC) -o $(TARGET) $(CFLAGS) $(M_SRC)

$(SERVER): $(S_SRC)
	$(CC) -o $(SERVER) $(CFLAGS) $(S_SRC)
