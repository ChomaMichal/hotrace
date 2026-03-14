/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:28:16 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/14 21:16:48 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hashmap.h"
#include "../inc/hotrace.h"
#include <linux/limits.h>

void	parse_chunks(t_state *state, t_data *data)
{
	int i;
	int len;

	i = 0;

	if (data->used == 0)
		len = data->bytes;
	else
	 	len = data->used - data->bytes;
	while (i < len)
	{
		if (state->expect == KEY)
			
		if (state->expect == VALUE)

	}
	return ;
}

static bool	read_chunks(t_data *data, t_state *state)
{
	data->cap = 65536;  //64KB
	data->used = 0;
	data->buff = malloc(data->cap);
	if (!data->buff)
		return (false);
	while (1)
	{
		data->bytes = read(0, data->buff + data->used, data->cap - data->used);
		if (data->bytes <= 0)
		{
			if (data->bytes < 0)
				return (false);
			break;
		}
		data->used = data->used + data->bytes;
		parse_chunks(state, data);
		if (data->used == data->cap)
		{
			data->cap *= 2;
			data->buff = realloc(data->buff, data->cap); ///realloc self implementen with calloc
			if (!data->buff)
				return (false);
		}
	}
	return (true);
}
void	get_input(void)
{
	t_data data;
	t_state	state;

	state.mode = BUILD;
	state.expect = KEY;

	while (1)
	{
		if (state.mode == BUILD)
			read_chunks(&data, &state);
		if (state.mode == SEARCH)
			return ;

	}
	return ;
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

void print_not_found(char *key)
{
  write(1, key, str_n_len(key));
  write(1, ": Not found\n", 12);
}

int main()
{
	t_mem_arena *arena;
	t_hashmap *hash_map;



/* 	arena = arena_create((size_t)8 * GIB);
	if (arena == NULL)
	{
	  return (write(2, "Arena creation failed", 1), 22);
	} */
	if (get_input(arena))
		return (1);
	hash_map = init_hashmap(arena);
	//FAILCHECK
	while (1)
	{
    	char *key = get_next_element(arena);
    	if (key == NULL)
    	  break;
    	char *value = get_next_element(arena);
    	if (value == NULL)
    	  break;
    	insert(hash_map, key, value, arena);
		//FAILCHECK
  	}
  	while (1)
  	{
    	char *key = get_next_element(arena);
    	if (key == NULL)
		{
    	  break;
    	}
    	char *value = find(hash_map, key);
    	if (value != NULL)
    	  write(1, value, str_n_len(value) + 1);
    	else
    	  print_not_found(key);
	}
  	free(arena);


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
