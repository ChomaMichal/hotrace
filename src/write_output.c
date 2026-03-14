/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:41:14 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/14 22:27:24 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hotrace.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	unsigned char		*source;

	dst = (unsigned char *) dest;
	source = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		dst[i] = source[i];
		i++;
	}
	return ((void *)dest);
}

int	write_in_buffer(char *value, char *key, char *buffer, size_t *used)
{
	char not_found[12] = ": Not found\n";

	if (value != NULL) //FOUND VALUE
	{
		int value_len = str_n_len(value) + 1;

		if (*used + value_len <= 1024 * KIB)
			ft_memcpy(&buffer[*used], value, value_len);
		else
		 	return (MEMORY_FULL);
		*used = *used + value_len;
	}
	else //NOT FOUND
	{
		int key_len = str_n_len(key);
		if (*used + key_len <= 1024 * KIB)
			ft_memcpy(&buffer[*used], key, key_len);
		else
		 	return (MEMORY_FULL);
		*used = *used + key_len;
		if (*used + 12 <= 1024 * KIB)
			ft_memcpy(&buffer[*used], not_found, 12);
		else
		 	return (MEMORY_FULL);
		*used = *used + key_len;
	}
	return (0);
}
