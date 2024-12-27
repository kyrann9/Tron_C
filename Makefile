
exec: Controler.o View_SDL.o View_Ncurses.o Model.o
	@gcc -o exec main.c Controler.o View_SDL.o View_Ncurses.o Model.o -lSDL2 -lncurses

Controler.o:Controler.c Controler.h
	@gcc -c Controler.c

View_SDL.o:View_SDL.c View_SDL.h
	@gcc -c View_SDL.c

View_Ncurses.o:View_Ncurses.c View_Ncurses.h
	@gcc -c View_Ncurses.c

Model.o:Model.c Model.h
	@gcc -c Model.c

.PHONY : clean
clean :
	rm -f *.o 

mrproper : clean
	rm -f exec
