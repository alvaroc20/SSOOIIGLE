DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
DIRHEA := include/
DIRBOOKS := libros/

CFLAGS :=  -I$(DIRHEA) -Wall -ansi
LDLIBS := -pthread -std=c++11
CC := g++

all : dirs threadFormat utils ssooiigle exe

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

threadFormat: 
	$(CC) -o $(DIROBJ)threadFormat.o $(DIRSRC)threadFormat.cpp $(CFLAGS) -c $(LDLIBS)

utils: 
	$(CC) -o $(DIROBJ)utils.o $(DIRSRC)utils.cpp $(CFLAGS) -c $(LDLIBS)

ssooiigle:
	$(CC) -o $(DIROBJ)SSOOIIGLE.o $(DIRSRC)SSOOIIGLE.cpp $(CFLAGS) -c $(LDLIBS)

exe:
	$(CC) -o $(DIREXE)SSOOIIGLE $(DIROBJ)SSOOIIGLE.o $(CFLAGS) $(LDLIBS)

test_a:
	./$(DIREXE)SSOOIIGLE "$(DIRBOOKS)21 LEYES DEL LIDERAZGO - JOHN C. MAXWELL.txt" escuela 3

test_b:
	./$(DIREXE)SSOOIIGLE "$(DIRBOOKS)VIVE TU SUEÑO - JOHN MAXWELL.txt" carecen 4

clean:
	rm -r $(DIREXE) $(DIROBJ)