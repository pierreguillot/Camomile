all: lv2_file_generator

lv2_file_generator: main.o
	gcc -o ../../Plugins/lv2_file_generator main.o

main.o: main.c
	gcc -o main.o -c main.c -W -Wall -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf lv2_file_generator
