include Makefile.config

target = blank_project.lnx
objects = lynx-160-102-16.o \
	  lynx-stdjoy.o \
	  ./gfx/spaceship.o\
	  ./gfx/star.o\
	  ./sound/song.o\
	  blank_project.o

all: $(target)

run: $(target)
	mednafen $(target)

$(target) : $(objects)
	$(CL) -t $(SYS) -o $@ $(objects)
	
clean:
	rm $(target) $(objects)
