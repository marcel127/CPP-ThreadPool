CC = g++
OBJS =  thread_test.o thread.o logger.o 

HEADERS = thread.hpp thread_exception.hpp

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
else
    CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3  
endif

a.out: link $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ -pthread

link:
	ln -sf ../logger/logger.hpp
	ln -sf ../logger/logger.cpp

%.o: %.cpp $(HEADERS) 
	$(CC) $(CFLAGS) -c $< 

.PHONY: clean
clean:
	rm  -rf *.o a.out logger* *.log 
