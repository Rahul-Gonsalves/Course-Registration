driver.out: driver.o rqueue.o
	g++ -g -Wall -std=c++11 driver.o rqueue.o -o driver.out

mytest.out: mytest.o rqueue.o
	g++ -g -Wall -std=c++11 mytest.o rqueue.o -o mytest.out

driver.o: driver.cpp
	g++ -Wall -std=c++11 -c driver.cpp

mytest.o: mytest.cpp
	g++ -Wall -std=c++11 -c mytest.cpp

rqueue.o: rqueue.cpp rqueue.h
	g++ -Wall -std=c++11 -c rqueue.cpp

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~*.hgch *#
	rm -f *~ *.h.gch *#

val: driver.out mytest.out
	valgrind -s --track-origins=yes ./mytest.out
#	valgrind -s --track-origins=yes ./driver.out

run: driver.out mytest.out
	./driver.out
	./mytest.out