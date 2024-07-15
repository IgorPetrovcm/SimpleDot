bottom: bottom.so

bottom.so: matches.o
	gcc -shared matches.o -o bottom.so

matches.o: matches.c
	gcc -c -fPIC matches.c -o matches.o

clean:
	rm -f matches.o
	rm -f bottom.so
