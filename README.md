## <code>C-RPG</code>
# @author: SilverfangOne

### Allgemein
- Diese RPG Game engine verwedet Sprites/Tiles mit der groe�e von 16x16 pixeln.
- Nutzt SNES aufl�sung f�r Tiles/Sprites: 256 x 224.
- Die eigentliche Aufl�sung soll dan �bers Game konfiguriert werden.

### Projekt bauen:
Einfach im Projekt Ordner <code>make</code> in der cmd ausf�hren.

### Libs die Verwendet werden:
- JSON: https://github.com/DaveGamble/cJSON/tree/master
- LOGGING: https://github.com/rxi/log.c
- SDL: https://www.libsdl.org/
- HASHMAP: https://github.com/tidwall/hashmap.c

### <code>Setup C ENV in Windows:</code>
> 1. download zip mingw64: https://winlibs.com/
> 2. put into C:\ (system drive)
> 3. set env path var to mingw64 bin
> 4. rename ming32-make to make 