/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:28:16 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/14 12:52:47 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hashmap.h"
#include "../inc/hotrace.h"
#include <linux/limits.h>

int read_all(t_mem_arena *arena)
{
  ssize_t i;
  char *buff;

  while (1)
  {
    buff = arena_push(arena, 64 * KIB);
	if (!buff)
		return (1);
    i = read(STDIN_FILENO, buff, 64 * KIB);
    if (i > 0 && buff[i - 1] == 0) // ?????????????????
	{
    	break;
    }
    if (i != 64 * KIB)
      break;
  }
  if (i == -1)
  {
    return (1); // error handle
  }
  buff[i] = 0;
  arena_pop_to(arena, (t_u64)buff + i);
  return (0);
}

size_t str_n_len(char *str)
{
  size_t i = 0;
  while (str[i] != '\n')
  {
    i++;
  }
  return (i);
}

char *get_next_element(t_mem_arena *arena)
{
  static char *last = NULL;
  char *this;

  if (last == NULL)
  {
    last = (void *)arena + sizeof(t_mem_arena);
    return (last);
  }
  this = last;
  while (*this != '\n')
    this++;
  this++;
  last = this;
  if (*last == '\n')
    return (NULL);
  if (*this == 0)
    return (NULL);
  return (this);
}

<<<<<<< HEAD
int main()
{
=======
void print_not_found(char *key) {
  write(1, key, str_n_len(key));
  write(1, ": Not found\n", 12);
}

int main() {
>>>>>>> main
  t_mem_arena *arena;
  t_hashmap *hash_map;
  arena = arena_create((size_t)8 * GIB);
  if (arena == NULL)
  {
    return (write(2, "Arena creation failed\n", 23), 1);
  }
  if (read_all(arena))
  	return (write(2, "ERROR\n", 6), 1);



  hash_map = init_hashmap(arena);
  while (1)
  {
    // printf("I am here\n");
    char *key = get_next_element(arena);
    if (key == NULL)
      break;
    char *value = get_next_element(arena);
    if (value == NULL)
      break;
    insert(hash_map, key, value, arena);
  }



  while (1)
  {
    char *key = get_next_element(arena);
    if (key == NULL) {
      break;
    }
    char *value = find(hash_map, key);
    if (value != NULL)
      write(1, value, str_n_len(value) + 1);
    else
      print_not_found(key);
  }
  free(arena);
  return (0);

  // READ STDIN

  /* - SPLIT INPUT IN 2 PHASES:
    1) key/value pairs
    2) search queries
  */

  /*
  PARSING
  - READ STDIN 						check
  - SPLIT INPUT IN 2 PHASES:			WIP
    1) key/value pairs
    2) search queries
  - DETECT EMPTY LINE AS SEPARATOR

  BUILD HASH TABLE
  - HASH KEY WITH ALGORITHM djb2, FNV-1a, sdbm
  - CALC INDEX IN TABLE
  - HANDLE COLLISIONS
  - SAVE KEY & VALUE

  SEARCH
  - HASH SEARCHWORD
  - CALC START INDEX
  - IF SLOT KEY == NULL -> NOT FOUND
  - IF SLOT KEY MATCHES -> PRINT VALUE
  - IF SLOT KEY EXISTS BUT NO MATCH -> LINEAR PROBING
  - STOP WHEN:
    - MATCH FOUND
    - NULL SLOT FOUND
    - OR YOU RETURNED TO START / TABLE FULL SAFETY

  OUTPUT
  - PRINT VALUE + '\n'
  - ELSE PRINT "keyword Not found.\n"
  */

  return (0);
}
