UNAME = $(shell uname)

ifeq ($(UNAME), Linux)  # Linux
	LDFLAGS = -ldl -Wl,-rpath='${ORIGIN}'
endif

ifeq ($(UNAME), Darwin)  # Mac
	CFLAGS = -arch x86_64 -arch i386
	LDFLAGS = -ldl -arch x86_64 -arch i386
endif

all: lv2_file_generator

lv2_file_generator: main.o
	gcc -o ../../Plugins/lv2_file_generator main.o ${LDFLAGS}

main.o: main.c
	gcc -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf lv2_file_generator
