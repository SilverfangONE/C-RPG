# Zielverzeichnisse

# Formatierung
format:
	clang-format -i --sort-includes --style=gnu src/editor/*.c src/engine/*.c src/engine/game_lib/*.c include/engine/*.h include/editor/*.h  

# as consol app 
game: 
	gcc -o rpg.exe src/lib/*.c src/engine/*.c src/engine/game_lib/*.c -I src/ -I include/ -I include/engine/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp ./lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp ./lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .
	
editor:
	gcc -o rpg_editor.exe src/lib/*.c src/engine/game_lib/*.c src/editor/*.c -I src/ -I include/ -I include/editor/ -I include/engine/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp ./lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp ./lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .

clean: 
	rm SDL3.dll 
	rm SDL3_image.dll
	rm rpg.exe
	rm rpg_editor.exe
# as gui app 
# gcc -o rpg.exe src/main.c src/cJSON.c src/log.c src/game.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 