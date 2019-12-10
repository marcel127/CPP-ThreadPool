CC = g++
OBJS =  thread_pool_test.o thread_pool.o singleton_logger.o logger.o thread.o
LIBS =  -lboost_system -lboost_thread -lpthread -lboost_chrono
HEADERS = waitable_queue.hpp thread.hpp thread_pool.hpp

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

.PHONY: link
link:
	ln -sf ../include/logger/logger.hpp
	ln -sf ../include/logger/logger.cpp
	ln -sf ../include/logger/singleton_logger.hpp
	ln -sf ../include/logger/singleton_logger.cpp
	ln -sf ../include/thread/thread.cpp
	ln -sf ../include/thread/thread.hpp
	ln -sf ../include/thread/thread_exception.hpp
	ln -sf ../include/waitable_queue/waitable_queue.hpp

.PHONY: clean
clean:
	rm  -rf *.o a.out *logger*  thread.hpp thread.cpp  *queue* thread_exception.hpp 
	