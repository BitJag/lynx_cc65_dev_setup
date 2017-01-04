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
# 	rm $(target) $(objects) #currently don't have a way to build graphics with a rule, so we don't want to remove the object files in the "gfx" and "sound" folders.
	rm -f *.s 
	rm -f *.o 
	rm -f *.lnx
