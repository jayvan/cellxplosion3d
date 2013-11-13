INCLUDES = \
    -I. \
    -I/usr/include/SDL


LIBS = \
	-lGL -lGLU -lSDL -lSDL_mixer

GPPFLAGS = \
    $(INCLUDES) \


ICCFLAGS = \
    $(INCLUDES)


CPP = g++ $(GPPFLAGS)
#CPP = g++ $(IPPFLAGS)

all: cellxplosion


.cpp.o:
	$(CPP) -g -c -o $@ $<
.c.o:
	$(CC) -g -c -o $@ $<

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)

compileobjs: $(OBJS)

cellxplosion: $(OBJS) Makefile
	$(CPP) -o cellxplosion $(OBJS) $(LIBS)

lib_tutorial: $(OBJS) Makefile
	ar rvs libsm $(OBJS)
	mv libsm libsm.a


clean:
	-rm *.o cellxplosion
