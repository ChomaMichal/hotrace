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


static bool	read_chunks(t_buffer *buf)
{
	buf->cap = 65536;  //64KB
	buf->used = 0;
	buf->string = ft_calloc(1, buf->cap);
	if (!buf->string)
		return (false);
	while (1)
	{
		buf->bytes = read(0, buf->string + buf->used, buf->cap - buf->used);
		if (buf->bytes <= 0)
		{
			if (buf->bytes < 0)
				return (false);
			break;
		}
		buf->used = buf->used + buf->bytes;
		if (buf->used == buf->cap)
		{
			buf->cap *= 2;
			buf->string = realloc(buf->string, buf->cap); ///realloc self implementen with calloc
			if (!buf->string)
				return (false);
		}
	}
	return (true);
}

int	main(int ac, char **av)
{
	(void) av;
	if (ac != 1)
		return (0);

	t_data data;
	t_mem_arena		*arena;

	arena = arena_create(8 * GIB);
	if (arena == NULL)
	{
		return (write(2, "Arena creation failed", 1), 22);
	}

	// READ STDIN
	if (!read_chunks(&data.buf))
		return (ERROR);
	if (VERBOSE)
		printf("%s", data.buf.string);



	/* - SPLIT INPUT IN 2 PHASES:
	  1) key/value pairs
	  2) search queries
	*/

	if (!pair_key_value(&data))
		return (ERROR);







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
