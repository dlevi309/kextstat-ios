CC = gcc-nofoundation
TARGET = kextstat
SRC = src/*.c
FLAGS = -Wall -O3 $(CFLAGS)
CFLAGS = -framework CoreFoundation -framework IOKit -lc++ -w -undefined dynamic_lookup -DEMBEDDED_HOST
SIGN   := ldid -Sent.xml

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(FLAGS) $(SRC)
	$(SIGN) $(TARGET)
