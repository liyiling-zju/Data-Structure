CC = g++
LIBS = BinarySearchTree.h

run : main
	./main

analysis : analysis.tex
	pdflatex $<

main : main.o $(LIBS)
	$(CC) -o $@ $^

main.o : main.cpp $(LIBS)
	$(CC) -o $@ -c $<

.PHONY : clean

clean :
	$(RM) main *.o *.aux *.log

realclean :
	$(MAKE) clean
	$(RM) *.pdf
