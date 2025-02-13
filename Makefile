# add format clang-format

# as consol app 
game: 
	gcc -o rpg.exe src/RPGE_GAME_main.c src/lib/*.c src/engine/*.c src/game/*.c src/util/*.c -I include/  -I include/engine/ -I include/game/ -I include/util/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .

editor:
	gcc -o rpg_editor.exe src/RPGE_EDITOR_main.c src/lib/*.c src/engine/*.c src/game/*.c src/editor/*.c src/util/*.c -I include/game/ -I include/util/ -I include/ -I include/editor/ -I include/engine/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .

clean: 
	rm SDL3.dll 
	rm SDL3_image.dll
	rm rpg.exe
	rm rpg_editor.exe
# as gui app 
# gcc -o rpg.exe src/main.c src/cJSON.c src/log.c src/game.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 