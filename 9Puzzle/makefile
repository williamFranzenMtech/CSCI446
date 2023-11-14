#Uses Gnu's compiler with the -g and -Wall flags.
CC = g++
CFLAGS = -g -Wall

#The source files used in this project.
SRCS = main.cpp LinkedList.cpp Queue.cpp

#The unlinked object files to be generated from each source.
OBJS = $(SRCS:.cpp=.o)

#The name of the executable.
TARGET = 9Puzzle.bin

#Generates the executable.
all: $(TARGET)

#Generates the executable, depends on the objects.
#$@ refers to the target, $^ refers to every dependency.
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

#Generates each object file, depends on the source files.
#$@ refers to the target, $< refers to the dependency.
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
