ifeq "$(shell arch)" "arm"
all:
else
dsc: dsc.c
	gcc -std=gnu99 -I/opt/local/include -L/opt/local/lib -D_FILE_OFFSET_BITS=64 -o dsc dsc.c -lfuse -framework CoreFoundation
endif

clean:
	rm -f dsc
