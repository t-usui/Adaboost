CXX=clang++
// CFLAGS=-c -O3 -Wall -I /usr/local/include/boost-1_37/ -g
CFLAGS=-c -O0 -Wall -I /opt/local/include/
// LDFLAGS=-L /usr/local/lib
DEBUG=-g
SOURCES=adaboost.cc parser.cc main.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=ada_boosting
VPATH=src

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(DEBUG) $(OBJECTS) -o $@

.cc.o:
	$(CXX) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -fr *.o *~ $(EXECUTABLE)
