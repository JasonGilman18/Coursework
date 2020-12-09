# makefile

# uncomment the version of the compiler that you are using
#clang++ is for Mac OS 
#C++ = clang++ -std=c++11
# g++ is for most Linux
C++ = g++ -std=c++11

all: dataserver client

clean:
	rm -f *.o dataserver client

netreqchannel.o: netreqchannel.hpp netreqchannel.cpp
	$(C++) -c -g netreqchannel.cpp

Request.o:  Request.hpp Request.cpp
	$(C++) -c -g Request.cpp
	
Semaphore.o:  Semaphore.hpp Semaphore.cpp
	$(C++) -c -g Semaphore.cpp -lpthread
	
Buffer.o:   Buffer.hpp Buffer.cpp Semaphore.o Request.o
	$(C++) -c -g Buffer.cpp

dataserver: dataserver.cpp netreqchannel.o 
	$(C++) -o dataserver dataserver.cpp netreqchannel.o -lpthread

client: client.cpp Semaphore.o Buffer.o netreqchannel.o
	$(C++) -o client client.cpp Request.o Semaphore.o Buffer.o netreqchannel.o -lpthread
