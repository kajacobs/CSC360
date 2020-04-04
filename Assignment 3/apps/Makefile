SOURCES =../io/file.c
PROGRAMS =test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 testval
DEBUG =-DDEBUG
CFLAGS =-Wall -g -std=c99
LIBS =-I.
% : %.c
	gcc $< $(SOURCES) -o $@ $(CFLAGS) $(LIBS) 

clean : 
	rm -f $(PROGRAMS)
	rm -rf *.dSYM
