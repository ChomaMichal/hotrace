/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:28:16 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/13 20:29:29 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hotrace.h"
#include <linux/limits.h>

void read_all(t_mem_arena *arena) {
  size_t i;
  char *buff;

  i = 0;
  while (1) {
    buff = arena_push(arena, 64 * KIB);
    i = read(1, buff, 64 * KIB);
    if (i != 64 * KIB)
      break;
  }
  if (i == -1) {
    exit(1); // error handle
  }
  buff[i] = 0;
  arena_pop_to(arena, (t_u64)buff + i);
}

char *get_next_element(t_mem_arena *arena) {
  static char *last = NULL;
  char *this;

  if (last == NULL) {
    last = (void *)arena + sizeof(t_mem_arena);
    return (last);
  }
  this = last;
  while (*this != '\n')
    this++;
  if (this == last)
    return (NULL);
  this++;
  if (*this == 0)
    return (NULL);
  last = this;
  return (this);
}

int main(int ac, char **av) {
  t_mem_arena *arena;

  arena = arena_create(8 * GIB);
  if (arena == NULL) {
    return (write(2, "Arena creation failed", 1), 22);
  }

  // READ STDIN
  read_all(arena, )

      /* - SPLIT INPUT IN 2 PHASES:
        1) key/value pairs
        2) search queries
      */

      if (!pair_key_value(&data)) return (ERROR);

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
