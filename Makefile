test: lab1.o vis.o
	gcc -o lab1.o vis.o -lm -Wall .

lab1.o: lab1.c
	gcc -c lab1.c

vis.o:
	gcc -c vis.c

clean: 
	rm -f lab1.o vis.o lab1