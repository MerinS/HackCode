CC = gcc
CFLAGS = -std=c11 -Wall -pthread -lm

TARGET = write-out-test
SERVER = evil-server
DETECTOR = FallDetector.o
SERIAL = serial_interface.o
FINAL = f_track
M_SRC = write_out.c
S_SRC = server.c
D_SRC = FallDetector.c FallDetector.h
SER_SRC = serial_interface.c

default: $(TARGET) $(SERVER) $(FINAL)

$(TARGET): $(M_SRC)
	$(CC) -o $(TARGET) $(CFLAGS) $(M_SRC)

$(SERVER): $(S_SRC)
	$(CC) -o $(SERVER) $(CFLAGS) $(S_SRC)

$(DETECTOR): $(D_SRC)
	$(CC) -c $(CFLAGS) $(D_SRC)

$(SERIAL): $(SER_SRC)
	$(CC) -c $(CFLAGS) $(SER_SRC)

$(FINAL): $(DETECTOR) $(SERIAL)
	$(CC) -o $(FINAL) $(CFLAGS) $(DETECTOR) $(SERIAL)

clean:
	rm -f $(FINAL) $(SERIAL) $(DETECTOR) $(SERVER) $(TARGET)
