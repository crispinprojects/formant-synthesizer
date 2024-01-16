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
 * MANIFEST: variable instances
 */

#include "var.h"

frame_ty	LastTarget;
double		f0[2];

double		f1[2];
double		f2[2];
double		f3[2];
double		f4[2];
double		f5[2];
double		f6[2];

double		bw1[2];
double		bw2[2];
double		bw3[2];
double		bw4[2];
double		bw5[2];
double		bw6[2];



double		av[2];
double		length;
double		s_f0;

double		s_f1;
double		s_f2;
double		s_f3;
double		s_f4;
double		s_f5;
double		s_f6;


double		s_bw1;
double		s_bw2;
double		s_bw3;
double		s_bw4;
double		s_bw5;
double		s_bw6;

double		s_av;
double		fnp;
double		fnz;
double		af;
double		ab;
double		a1;
double		a2;
double		a3;
double		a4;
double		a5;
double		a6;
double		asp;
int		f0_change;
