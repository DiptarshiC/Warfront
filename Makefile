
# Example 14
EXE=War

# Main target
all: $(EXE)

#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32
CLEAN=del *.exe *.o *.a War
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies

basic_shapes.o: src/basic_shapes.c headers/basic_shapes.h 
	gcc -o basic_shapes.o  -c src/basic_shapes.c   $(LIBS)
vehicles.o: src/vehicles.c headers/vehicles.h src/basic_shapes.c headers/basic_shapes.h
	gcc -o vehicles.o -c src/vehicles.c  $(LIBS)
buildings.o: src/buildings.c headers/buildings.h src/basic_shapes.c headers/basic_shapes.h
	gcc -o buildings.o -c src/buildings.c  $(LIBS)
War.o: 3D.c CSCIx229.h
	gcc -o War.o -c 3D.c
fatal.o: fatal.c CSCIx229.h
loadtexbmp.o: loadtexbmp.c CSCIx229.h
print.o: print.c CSCIx229.h
errcheck.o: errcheck.c CSCIx229.h
object.o: object.c CSCIx229.h

#  Create archive
CSCIx229.a:fatal.o loadtexbmp.o print.o errcheck.o object.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -c $(CFLG) $<
# Link

War:War.o CSCIx229.a basic_shapes.o vehicles.o buildings.o
	gcc -O3 -o $@ $^   $(LIBS)

#  Clean
clean:
	$(CLEAN)

