#ifndef HASHMAP_H
#define HASHMAP_H

#define HASHMAP_SIZE 1024
#include "hotrace.h"

typedef struct s_hashmap
{
	struct s_hashmap *next;
	char *value;
	char *key;
}	t_hashmap;

t_hashmap	*init_hashmap(t_mem_arena *arena);
void		insert(t_hashmap *map, char *key, char *value, t_mem_arena *arena);
char		*find(t_hashmap *map, char *key);

uint32_t	hash_key(const char *key);

#endif
