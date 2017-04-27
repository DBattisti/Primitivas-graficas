GCC = gcc -o
LINKS = -lglut -lGLU -lGL -lm
PRIMITIVES = ../object3D.c ../graphicPrimitives.c
# targets:

all: graphProgram

run: graphProgram
	./graphProgram

build: clean graphProgram

clean:
	rm -f graphProgram

graphProgram: $(PRIMITIVES) graphProgram.c
	$(GCC) graphProgram $(PRIMITIVES) graphProgram.c $(LINKS)
