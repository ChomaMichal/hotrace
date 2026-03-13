/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 20:44:23 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/13 21:47:25 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/hotrace.h"

uint32_t	hash_key(const char *key)
{
	uint32_t	hash;

	hash = 0x811C9DC5;
	while (*key != '\n')
	{
		hash = (hash ^ *key) * 0x01000193; //the magic number is a
		// prime number for hashing purposes
		key++;
	}
	return (hash);
}
