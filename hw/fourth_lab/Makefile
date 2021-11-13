CC = c++
CFLAGS = -c -Wall
SOURCES = first.cpp abs.cpp cos.cpp exp.cpp factorial.cpp getRad.cpp ln.cpp showLogo.cpp pow.cpp sin.cpp CalcXY.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTEBLE = App

all: $(SOURCES) $(EXECUTEBLE)


$(EXECUTEBLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -rf $(OBJECTS) $(EXECUTEBLE)