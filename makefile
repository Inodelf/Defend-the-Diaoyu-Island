prefix=/usr/local
exec_prefix = ${prefix}

LIBS = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
CXX=g++


IMAGE=SDL_image
objects=main.o background.o
game:game.cpp
	$(CXX) -o game game.cpp $(LIBS)  
clean:
	test -e game
	rm game ;
	 echo "file no"
