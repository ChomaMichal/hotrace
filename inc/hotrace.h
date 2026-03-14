/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:22:12 by pjelinek          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/03/14 12:15:43 by pjelinek         ###   ########.fr       */
=======
/*   Updated: 2026/03/14 14:37:43 by pjelinek         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
#define HOTRACE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// #include "defines.h"
// #include "structs.h"

#define KIB 1024
#define MIB 1048576
#define GIB 1073741824

typedef int8_t t_i8;
typedef int16_t t_i16;
typedef int32_t t_i32;
typedef int64_t t_i64;
typedef uint8_t t_u8;
typedef uint16_t t_u16;
typedef uint32_t t_u32;
typedef uint64_t t_u64;

typedef t_i8 t_b8;
typedef t_i32 t_b32;

typedef struct s_struct {
  t_u64 capacity;
  t_u64 pos;
} t_mem_arena;

// ARENA
t_mem_arena *arena_create(t_u64 capacity);
void *arena_push(t_mem_arena *arena, t_u64 size);
void arena_pop(t_mem_arena *arena, t_u64 size);
void arena_pop_to(t_mem_arena *arena, t_u64 pos);
void arena_clear(t_mem_arena *arena);

#endif /* HOTRACE_H */
