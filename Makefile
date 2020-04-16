output : main.o buffer.o commands.o getblk.o brelse.o help.o
	g++ -pthread main.o buffer.o commands.o getblk.o brelse.o help.o -o bufferCache

main.o: main.cpp
	g++ -c main.cpp

buffer.o: buffer.cpp buffer.h
	g++ -c buffer.cpp

commands.o: commands.cpp commands.h
	g++ -c commands.cpp

getblk.o: getblk.cpp
	g++ -c getblk.cpp

brelse.o: brelse.cpp
	g++ -c brelse.cpp

help.o: help.cpp
	g++ -c help.cpp

clean:
	rm *.o
