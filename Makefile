CC = gcc
CFLAGS = -std=c11 -Wall -pthread -lm

WRITE_OUT = write_out.o
SERVER = evil-server
DETECTOR = FallDetector.o
SERIAL = serial_interface.o
FINAL = f_track
M_SRC = write_out.c write_out.h
S_SRC = server.c
D_SRC = FallDetector.c FallDetector.h
SER_SRC = serial_interface.c

default: $(TARGET) $(SERVER) $(FINAL)

$(SERVER): $(S_SRC)
	$(CC) -o $(SERVER) $(CFLAGS) $(S_SRC)

$(DETECTOR): $(D_SRC)
	$(CC) -c $(CFLAGS) $(D_SRC)

$(SERIAL): $(SER_SRC)
	$(CC) -c $(CFLAGS) $(SER_SRC)

$(WRITE_OUT): $(M_SRC)
	$(CC) -c $(CFLAGS) $(M_SRC)

$(FINAL): $(DETECTOR) $(SERIAL) $(WRITE_OUT)
	$(CC) -o $(FINAL) $(CFLAGS) $(DETECTOR) $(SERIAL) $(WRITE_OUT)

clean:
	rm -f $(FINAL) $(SERIAL) $(DETECTOR) $(SERVER) $(TARGET)
