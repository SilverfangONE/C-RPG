all: 
	gcc -o rpg.exe src/main.c src/cJSON.c src/log.c src/game.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 
	cp ./lib/SDL3/i686-w64-mingw32/bin/SDL3.dll .
