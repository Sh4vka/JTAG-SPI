CC = g++
SRC1 = jtag.cpp
SRC2 = spi.cpp
TARGET1 = jtag
TARGET2 = spi

all: jtag spi

jtag:
	$(CC) $(SRC1) -o $(TARGET1)
	./$(TARGET1)
	rm $(TARGET1)

spi:
	$(CC) $(SRC2) -o $(TARGET2)
	./$(TARGET2)
	rm $(TARGET2)
	
.PHONY: all jtag spi
