/*
 *	recite - english text speech synthesizer
 *	Copyright (C) 1993 Peter Miller.
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
 * MANIFEST: interface definition for phonemes/var.c
 */

#ifndef VAR_H
#define VAR_H

#ifdef __STDC__ //compiler conforms to ISO Standard C
# define _(x) x
#else
# define _(x) ()
# define const
#endif

#define SIZEOF(a) (sizeof(a) / sizeof(a[0]))
#define ENDOF(a) ((a) + SIZEOF(a))


#include "features.h"

extern	frame_ty	LastTarget;
extern	double		f0[2];

extern	double		f1[2];
extern	double		f2[2];
extern	double		f3[2];
extern	double		f4[2];
extern	double		f5[2];
extern	double		f6[2];


extern	double		bw1[2];
extern	double		bw2[2];
extern	double		bw3[2];
extern	double		bw4[2];
extern	double		bw5[2];
extern	double		bw6[2];


extern	double		av[2];
extern	double		length;
extern	double		s_f0;

extern	double		s_f1;
extern	double		s_f2;
extern	double		s_f3;
extern	double		s_f4;
extern	double		s_f5;
extern	double		s_f6;

extern	double		s_bw1;
extern	double		s_bw2;
extern	double		s_bw3;
extern	double		s_bw4;
extern	double		s_bw5;
extern	double		s_bw6;

extern	double		s_av;
extern	double		fnp;
extern	double		fnz;
extern	double		af;
extern	double		ab;
extern	double		a1;
extern	double		a2;
extern	double		a3;
extern	double		a4;
extern	double		a5;
extern	double		a6;
extern	double		asp;
extern	int		f0_change;

#endif /* VAR_H */
