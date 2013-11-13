
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


.cpp.o:
	$(CPP) -g -c -o $@ $<
.c.o:
	$(CC) -g -c -o $@ $<

OBJS = \
    SDL_OGL.o \
    main.o \
    SoundManager.o


compileobjs: $(OBJS)

HEADERS = \
    SDL_OGL.h \
    SoundManager.h


sample_tutorial: $(HEADERS) $(OBJS) Makefile
	$(CPP) -o cellxplosion $(OBJS) $(LIBS)

lib_tutorial: $(HEADERS) $(OBJS) Makefile
	ar rvs libsm $(OBJS)
	mv libsm libsm.a


clean:
	-rm *.o cellxplosion
