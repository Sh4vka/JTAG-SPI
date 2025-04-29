CC = g++
SRC = jtag.cpp
TARGET = jtag

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) 

