#include "../inc/hashmap.h"

t_hashmap *init_hashmap(t_mem_arena *arena)
{
  t_hashmap *rt;
  size_t i;

  i = 0;
  rt = arena_push(arena, HASHMAP_SIZE * sizeof(t_hashmap));

  while (i != HASHMAP_SIZE)
  {
    rt[i].key = NULL;
    i++;
  }
  return (rt);
}

void insert(t_hashmap *map, char *key, char *value, t_mem_arena *arena)
{
  uint32_t hash;
  t_hashmap *idk;

  hash = hash_key(key);
  hash = hash & (HASHMAP_SIZE - 1); // do magic number here
  if (map[hash].key == NULL)
  {
    map[hash].key = key;
    map[hash].value = value;
    map[hash].next = NULL;
    return;
  }
  idk = map[hash].next;
  if (idk != NULL)
  {

    while (idk->next != NULL)
	{
      idk = idk->next;
    }
  }
  idk = arena_push(arena, sizeof(t_hashmap));
  idk->value = value;
  idk->key = key;
  idk->next = NULL;
}

static bool str_cmp_cust(char *s1, char *s2)
{
  size_t i;

  i = 0;
  while (s1[i] == s2[2])
  {
    if (s1[i] == '\n')
      return true;
  }
  return false;
}

char *find(t_hashmap *map, char *key)
{
  uint32_t hash;
  t_hashmap *idk;

  hash = hash_key(key);
  hash = hash & (HASHMAP_SIZE - 1); // do magic number here
  if (map[hash].key == NULL)
    return (NULL);
  if (map[hash].next == NULL)
  {
    return map[hash].value;
  }
  if (str_cmp_cust(key, map[hash].key))
    return map[hash].value;

  idk = map[hash].next;
  while (idk != NULL)
  {
    if (str_cmp_cust(key, idk->key))
	{
      return (idk->value);
    }
  }
  return (NULL);
}
