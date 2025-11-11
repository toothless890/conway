
CFLAGS=-g -Wall -Werror -Ofast

.PHONY=check

all: drawFrame

makeTexture.o: makeTexture.c makeTexture.h

makeTexture: makeTexture.o
	gcc $(CFLAGS) makeTexture.c -o makeTexture

drawFrame.o: drawFrame.c makeTexture.h

drawFrame: drawFrame.o makeTexture.o
	gcc $(CFLAGS) -o drawFrame drawFrame.o makeTexture.o -I./include -L./lib -lSDL2

run: all
	./drawFrame

exe:
	x86_64-w64-mingw32-gcc -o drawFrame.exe drawFrame.c makeTexture.c makeTexture.h -I/usr/x86_64-w64-mingw32/include/SDL2 -L/usr/x86_64-w64-mingw32/lib -lSDL2 


clean:
	@echo -n Cleaning...
	@rm *~ *.o drawFrame makeTexture 2>/dev/null || true
	@echo done
