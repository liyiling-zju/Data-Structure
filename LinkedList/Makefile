CC = g++
LIBS = LinkedList.h

run : test
	./test

test : test.o $(LIBS)
	$(CC) -o $@ $^

test.o : test.cpp  $(LIBS)
	$(CC) -o $@ -c  $<

.PHONY : clean

clean :
	$(RM) test *.o
