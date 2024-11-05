CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./

BIN=./bin/tf-animate
SRCS=./src/transformers.cpp ./src/gl_framework.cpp ./src/shader_util.cpp ./src/texture.cpp 
INCLUDES=./src/gl_framework.hpp ./src/shader_util.hpp ./src/transformers.hpp ./src/vector_prime.hpp ./src/optimus_prime.hpp ./src/texture.hpp 

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	mkdir -p ./bin
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
