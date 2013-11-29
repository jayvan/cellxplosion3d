SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(SOURCES:.cpp=.d)
INCLUDES = -I. -I/usr/include/SDL -Llib
LDFLAGS = $(INCLUDES) $(shell pkg-config --libs lua5.1) -llua5.1 -lGL -lGLU -lglut -lSDL -lSDL_mixer -lSOIL
CPPFLAGS = $(INCLUDES) $(shell pkg-config --cflags lua5.1) -std=c++0x
CXXFLAGS = $(CPPFLAGS) -W -Wall -g -std=c++0x
CXX = g++
MAIN = cellxplosion

all: $(MAIN)

depend: $(DEPENDS)

clean:
	rm -f *.o *.d $(MAIN)

$(MAIN): $(OBJECTS)
	@echo Creating $@...
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	@echo Compiling $<...
	$(CXX) -o $@ -c $(CXXFLAGS) $<

%.d: %.cpp
	@echo Building $@...
	set -e; $(CC) -M $(CPPFLAGS) $< \
                  | sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
                [ -s $@ ] || rm -f $@

include $(DEPENDS)
