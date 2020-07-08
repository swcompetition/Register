CC=g++-10.1
CFLAGS=-Wall -O3
TARGET=app.out
OBJS=test.o\
	Register.o\
	RMem.o\
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -rf ./*.out ./*.o