CC = gcc
CFLAGS = -std=c11 -Wall -pthread

TARGET = write-out-test
SERVER = evil-server
M_SRC = write_out.c
S_SRC = server.c

default: $(TARGET) $(SERVER)

$(TARGET): $(M_SRC)
	$(CC) -o $(TARGET) $(CFLAGS) $(M_SRC)

$(SERVER): $(S_SRC)
	$(CC) -o $(SERVER) $(CFLAGS) $(S_SRC)
