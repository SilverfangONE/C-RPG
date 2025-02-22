# add format clang-format

format:
	clang-format --style=Microsoft -i src/RPGE_GAME_main.c src/lib/*.c src/engine/*.c  src/engine/objects/*.c src/engine/container/*.c src/engine/decoder_engine/json/*.c src/engine/graphics/*.c src/engine/graphics/ui_elements/*.c src/game/*.c src/game/objects/*.c src/util/*.c src/lib/*.h src/engine/*.h include/engine/objects/*.h include/engine/container/*.h src/engine/decoder_engine/json/*.h src/engine/graphics/*.h src/engine/graphics/ui_elements/*.h src/game/*.h src/game/object/*.h src/util/*.h

# as consol app 
game: 
	gcc -o rpg.exe src/RPGE_GAME_main.c src/lib/*.c src/engine/*.c src/engine/container/*.c  src/engine/objects/*.c src/engine/decoder_engine/json/*.c src/engine/graphics/*.c src/engine/graphics/ui_elements/*.c src/game/*.c src/game/objects/*.c src/util/*.c -I include/  -I include/engine/ -I include/engine/objects/ -I include/engine/container -I include/engine/decoder_engine/json/ -I include/engine/graphics/ui_elements -I include/engine/graphics/ -I include/game/ -I include/game/objects/ -I include/util/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .

editor:
	gcc -o editor.exe src/RPGE_EDITOR_main.c src/editor/*.c src/editor/menus/*.c src/lib/*.c src/engine/*.c src/engine/container/*.c  src/engine/objects/*.c src/engine/decoder_engine/json/*.c src/engine/graphics/*.c src/engine/graphics/ui_elements/*.c src/game/*.c src/game/objects/*.c src/util/*.c -I include/ -I include/editor/ -I include/editor/menus/  -I include/engine/ -I include/engine/objects/ -I include/engine/container -I include/engine/decoder_engine/json/ -I include/engine/graphics/ui_elements -I include/engine/graphics/ -I include/game/ -I include/game/objects/ -I include/util/ -I include/lib/ -I lib/SDL3-3.2.0/x86_64-w64-mingw32/include/ -I lib/SDL3_image-3.1.1/x86_64-w64-mingw32/include/ -L lib/SDL3-3.2.0/x86_64-w64-mingw32/lib/  -L lib/SDL3_image-3.1.1/x86_64-w64-mingw32/lib/ -lSDL3 -lSDL3_image -mconsole -DLOG_USE_COLOR
	cp lib/SDL3-3.2.0/x86_64-w64-mingw32/bin/SDL3.dll .
	cp lib/SDL3_image-3.1.1/x86_64-w64-mingw32/bin/SDL3_image.dll .

clean: 
	rm SDL3.dll 
	rm SDL3_image.dll
	rm rpg.exe
	rm editor.exe
# as gui app 
# gcc -o rpg.exe src/main.c src/cJSON.c src/log.c src/game.c -I src/ -I include/ -I lib/SDL3/i686-w64-mingw32/include/ -L lib/SDL3/i686-w64-mingw32/lib/ -lSDL3 -mwindows 