/*
 *	recite - english text speech synthesizer
 *	Copyright (C) 1991, 1992, 1993 Peter Miller.
 *	All rights reserved.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 1, or (at your option)
 *	any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * MANIFEST: interface definition for common/mem.c
 */

#ifndef MEM_H
#define MEM_H

#include <stddef.h>
//mem
char *enlarge(size_t *length, char **base,size_t size);	
char * mem_alloc(size_t n);
char * mem_alloc_clear(size_t n);
void mem_change_size(char **cpp, size_t	n);
void mem_free(char *cp);

#endif /* MEM_H */
