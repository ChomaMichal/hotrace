/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:05 by pjelinek          #+#    #+#             */
/*   Updated: 2026/03/13 16:54:28 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_buffer
{
	unsigned int	cap;
	unsigned int	used;
	char			*string;
	int				bytes;
}	t_buffer;

typedef struct data
{
	char			**table;
	unsigned int	index;
	char 			*key;
	char 			*value;
	t_buffer		buf;
}	t_data;

#endif /* STRUCTS_H */
