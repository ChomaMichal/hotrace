#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE 1024;
#include "hotrace.h"

typedef struct s_hashmap {
  s_hashmap *next;
  char *value;
  char *key;
} t_hashmap;

s_hashmap *init_hashmap(t_mem_arena *arena);
void insert(t_hashmap *map, char *key, char *value);
char *find(t_hashmap *map, char *key);

#endif
