CC = gcc

TARGET = meg6

CFLAGS = -std=c17 \
        -Ibinary \
        -Icomponents \
        -Icomponents/cpu \
        -Iinstructions \
        -Iio

SRC = main.c \
      binary/binary.c \
      components/cpu/control_unit.c \
      components/cpu/registrars.c \
      components/memory.c \
      instructions/instructions.c \
      io/io_stuff.c \
      io/read_file.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean: 
	rm -f $(OBJ) $(TARGET)