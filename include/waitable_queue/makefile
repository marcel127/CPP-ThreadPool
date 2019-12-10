CC = g++
OBJS =  waitable_queue_test.o singleton_logger.o logger.o thread.o
LIBS =  -lboost_system -lboost_thread -lpthread -lboost_chrono
HEADERS = waitable_queue.hpp thread.hpp

DEBUG ?= 1
ifeq ($(DEBUG), 1)
    CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g 
else
    CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3  
endif

a.out: $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cpp $(HEADERS) 
	$(CC) $(CFLAGS) -c $< 

link:
	ln -sf ../logger/logger.hpp
	ln -sf ../logger/logger.cpp
	ln -sf ../logger/singleton_logger.hpp
	ln -sf ../logger/singleton_logger.cpp
	ln -sf ../thread/thread.cpp
	ln -sf ../thread/thread.hpp
	ln -sf ../thread/thread_exception.hpp

.PHONY: clean
clean:
	rm  -rf *.o a.out *logger* mutex* thread* shared_ptr*
