debug = g++ -ansi -pedantic-errors -Wall -Wextra -g
release = g++ -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
clang = clang++

all:
	$(clang)  logger.cpp  logger_test.cpp -o clang.out
	$(debug)  logger.cpp  logger_test.cpp -o deb.out 
	$(release)  logger.cpp  logger_test.cpp -o rel.out 
	
rel:
	./rel.out

deb:
	./deb.out

clean:
	rm -f *.out *.log *.o