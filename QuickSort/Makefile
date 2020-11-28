CC = g++

run : main
	./main

analysis : analysis.tex
	pdflatex $<

main : main.o 
	$(CC) -o $@ $^

main.o : main.cpp
	$(CC) -o $@ -c $<

.PHONY : clean

clean :
	$(RM) main *.o *.aux *.log

realclean :
	$(MAKE) clean
	$(RM) *.pdf data.*
