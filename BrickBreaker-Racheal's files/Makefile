CC = g++
CFLAGS = -w -lSDL2 -lSDL2_image
OBJFILES = Brick.o Paddle.o texture.o Ball.o helper.o main.o
TARGET = Brick_Breaker

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
