#ifndef RPGE_G_CONTEXT
#define RPGE_G_CONTEXT

typedef struct CONTEXT_RPG {
    char* pName;
} CONTEXT_RPG;

CONTEXT_RPG* init_RPG(char*);
void destory_CONTEXT_RPG(CONTEXT_RPG*);
void destory_VOID_CONTEXT_RPG(void* );
#endif