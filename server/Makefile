CC = c++
CFLAGS = -c -Wall
SOURCES = main.cpp additionalFunctions.cpp findFile.cpp myClass.cpp sockClass.cpp logClass.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTEBLE = App

all: $(SOURCES) $(EXECUTEBLE)


$(EXECUTEBLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@


.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -rf $(OBJECTS) $(EXECUTEBLE)