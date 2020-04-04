SOURCES =../io/file.c
PROGRAMS =test format testlists testdir testfiles addfile removefile testargs
DEBUG =-DDEBUG
CFLAGS =-Wall -g -std=c99
LIBS =-I.
% : %.c
	gcc $< $(SOURCES) -o $@ $(CFLAGS) $(LIBS) 

clean : 
	rm -f $(PROGRAMS)
