# as consol app 
all: 
	gcc -o rpg.exe src/*.c -I src/ -I include/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	
# cp lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
# cp lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .
# as gui app 
# gcc -o rpg.exe src/main.c src/cJSON.c src/log.c src/game.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 