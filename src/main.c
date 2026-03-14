/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:28:16 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/14 21:41:22 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hashmap.h"
#include "../inc/hotrace.h"
#include <limits.h>

int read_all(t_mem_arena *arena) {
  ssize_t i;
  char *buff;
  int rt;

  while (1) {
    buff = arena_push_unaligned(arena, 64 * KIB);
    // FAILCHECK
    // printf("Arena: %p\n", arena);
    // printf("Buff : %p\n", buff);
    // printf("Buff  == arena + 16 : %i\n", (t_u64)buff == (t_u64)arena + 16);
    // printf("Arena->pos %lu\n", arena->pos);

    i = read(STDIN_FILENO, buff, 64 * KIB);
    arena_pop_to_pointer(arena, buff + i);
    // printf("i = %lu\n", i);
    // printf("Buff= %p\n", buff);
    // printf("Arena->pos 2 %lu\n", arena->pos);
    // i = 0 --> buff[-1] !!
    if (i == 0 || buff[i - 1] == 0) {
      rt = 0;
      break;
    }
    if (buff[0] == '\n' && i == 1) {
      rt = 1;
      break;
    }
  }
  if (i == -1) {
    return (-1); // error handle
  }
  buff[i] = 0;
  return (rt);
}

char *read_one(t_mem_arena *arena) {
  ssize_t i;
  char *buff;
  ssize_t counter;

  buff = arena_push_unaligned(arena, 64 * KIB);
  while (1) {
    // FAILCHECK
    i = read(STDIN_FILENO, buff, 64 * KIB - 1);
    // i = 0 --> buff[-1] !!
    buff[i] = 0;
    counter = 0;
    while (counter < i) {
      if (buff[counter] == '\n') {
        return (arena_pop_to_pointer(arena, (void *)buff + i), buff);
      }
      if (buff[counter] == 0)
        break;
      counter++;
    };
    if (i == -1) {
      return (NULL);
    }
    if (i == 0) {
      return (NULL);
    }
    arena_pop_to_pointer(arena, (void *)buff + i);
    buff = arena_push_unaligned(arena, 64 * KIB);
  }
  return (buff);
}

size_t str_n_len(char *str) {
  size_t i = 0;
  while (str[i] != '\n') {
    i++;
  }
  return (i);
}

char *get_next_element_user_input(t_mem_arena *arena, char *last_word) {
  if (*last_word != '\n')
    last_word++;
  while (1) {
    if (*last_word == '\n') {
      last_word++;
      if (*last_word == 0)
        return (read_one(arena));
      else
        return (last_word);
    }
    last_word++;
  }
}

char *get_next_element(t_mem_arena *arena, int *end) {
  static char *last = NULL;
  char *this;

  if (last == NULL) {
    last = (void *)arena + sizeof(t_mem_arena);
    return (last);
  }
  this = last;
  while (*this != '\n')
    this++;
  this++;
  last = this;
  if (*last == '\n') {
    *end = 0;
    return (NULL);
  }
  if (*last == 0) {
    *end = 1;
    return (NULL);
  }
  return (this);
}

char *get_next_element_can_be_nl(char *last) {
  while (*last != '\n')
    last++;
  last++;
  if (*last == 0)
    return (NULL);
  return (last);
}

void print_not_found(char *key) {
  write(1, key, str_n_len(key));
  write(1, ": Not found\n", 12);
}

int file_io(t_mem_arena *arena) {
  t_hashmap *hash_map;
  int end;
  char *key;
  char *value;

  value = NULL;
  end = 0;
  hash_map = init_hashmap(arena);
  // FAILCHECK
  while (1) {
    key = get_next_element(arena, &end);
    if (key == NULL)
      break;
    value = get_next_element(arena, &end);
    if (value == NULL)
      break;
    insert(hash_map, key, value, arena);
    // FAILCHECK
  }
  if (end == 1) {
    free(arena);
    return (1);
  }
  if (key == NULL)
    key = value;
  if (key == NULL) {
    free(arena);
    return (0);
  }

  while (1) {
    key = get_next_element_can_be_nl(key);
    if (key == NULL || end == 1) {
      break;
    }
    value = find(hash_map, key);
    if (value != NULL)
      write(1, value, str_n_len(value) + 1);
    else
      print_not_found(key);
  }
  free(arena);
  return (0);
}

int user_io(t_mem_arena *arena) {
  t_hashmap *hash_map;
  char *key;
  int end;

  hash_map = init_hashmap(arena);
  // FAILCHECK
  while (1) {
    char *key = get_next_element(arena, &end);
    // printf("key ==\n%s ==\n", key);

    if (key == NULL)
      break;
    char *value = get_next_element(arena, &end);
    // printf("value ==\n%s ==\n", value);
    if (value == NULL)
      break;
    insert(hash_map, key, value, arena);
    // FAILCHECK
  }

  if (end == 1) {
    free(arena);
    return (1);
  }
  // printf("searching\n");
  key = read_one(arena);
  while (1) {
    if (key == NULL) {
      break;
    }
    // printf("key ===\n%s===\n", key);
    char *value = find(hash_map, key);
    // printf("value ===\n%s===\n", value);
    if (value != NULL)
      write(1, value, str_n_len(value) + 1);
    else
      print_not_found(key);
    key = get_next_element_user_input(arena, key);
  }
  free(arena);
  return (0);
}

int main() {
  t_mem_arena *arena;
  int i;
  arena = arena_create((size_t)8 * GIB);
  if (arena == NULL) {
    return (write(2, "Arena creation failed", 1), 22);
  }
  i = read_all(arena);
  if (i == 0) {
    return (file_io(arena));
  }
  if (i == 1)
    return (user_io(arena));

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
