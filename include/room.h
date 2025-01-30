#ifndef ROOM
#define ROOM 

typedef struct {
	int x;
	int y;
};

typedef enum {
	MENU,
	WORLD,
	COMBAT
} RoomType;

typedef struct {
	long long id;
	char* tilesetPath;
	int** tilesetMap;
	RoomType type;
} Room;

Room* loadRoom();

#endif
