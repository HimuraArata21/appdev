OBJ = screen.o testscreen.o comm.o sound.o
APPNAME = screentest

#linking rule
$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lcurl

#conpiling rule
%.o : %.c
	gcc -c -o $@ $<

#cleaning rule
clean :
	rm $(APPNAME) $(OBJ)

#archiving rule
zip :
	tar cf appdev.tar *.c *.h makefile


