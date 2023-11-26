/*
 * Copyright (C) 
 * (C) 2022 Alan Crispin
 * (C) 1993 Peter Miller.
 * A re-implementation of formant generation code. 
 * The original code was developed by the late Peter Miller 
 * (Recite project). This file contains the new method
 * 
 * 		convert_frame_to_klatt_frame()
 * 
 * This allows the generated formants to be used
 * by the Klatt Cascade-Parallel Formant Speech Synthesizer 
 * by Reece H. Dunn found at  https://github.com/rhdunn/klatt
 *  
 * The code can be compiled with gcc version 11.2.1 20220127.
 * 
 * Peter Millers Wiki page with links to his software projects is
 * https://en.wikipedia.org/wiki/Peter_Miller_(software_engineer)
 * 
 * The original Copyright states   
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
 * MANIFEST: interface definition for common/frame.c
 */

#ifndef FRAME_H
#define FRAME_H



#include <stddef.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


#include "parwave.h"


typedef struct pars_ty pars_ty;

struct pars_ty
{
	short	F0hz10;	/* 0 */
	short	AVdb;	/* 1 */
	short	F1hz;	/* 2 */
	short	B1hz;	/* 3 */
	short	F2hz;	/* 4 */
	short	B2hz;	/* 5 */
	short	F3hz;	/* 6 */
	short	B3hz;	/* 7 */
	short	F4hz;	/* 8 */
	short	B4hz;	/* 9 */
	short	F5hz;	/* 10 */
	short	B5hz;	/* 11 */
	short	F6hz;	/* 12 */
	short	B6hz;	/* 13 */
	short	FNZhz;	/* 14 */
	short	BNZhz;	/* 15 */
	short	FNPhz;	/* 16 */
	short	BNPhz;	/* 17 */
	short	AP;	/* 18 */
	short	Kopen;	/* 19 */
	short	Aturb;	/* 20 */
	short	TLTdb;	/* 21 */
	short	AF;	/* 22 */
	short	Kskew;	/* 23 */
	short	A1;	/* 24 */
	short	B1phz;	/* 25 */
	short	A2;	/* 26 */
	short	B2phz;	/* 27 */
	short	A3;	/* 28 */
	short	B3phz;	/* 29 */
	short	A4;	/* 30 */
	short	B4phz;	/* 31 */
	short	A5;	/* 32 */
	short	B5phz;	/* 33 */
	short	A6;	/* 34 */
	short	B6phz;	/* 35 */
	short	ANP;	/* 36 */
	short	AB;	/* 37 */
	short	AVpdb;	/* 38 */
	short	Gain0;	/* 39 */
};

/* default values for pars array from .doc file */
static pars_ty def_pars =
{
	1000,	/* F0hz10 */
	60,	/* AVdb */
	500,	/* F1hz */
	60,	/* B1hz */
	1500,	/* F2hz */
	90,	/* B2hz */
	2800,	/* F3hz */
	150,	/* B3hz */
	3250,	/* F4hz */
	200,	/* B4hz */
	3700,	/* F5hz */
	200,	/* B5hz */
	4990,	/* F6hz */
	500,	/* B6hz */
	280,	/* FNZhz */
	90,	/* BNZhz */
	280,	/* FNPhz */
	90,	/* BNPhz */
	0,	/* AP */
	30,	/* Kopen */
	0,	/* Aturb */
	0,	/* TLTdb */
	0,	/* AF */
	0,	/* Kskew */
	0,	/* A1 */
	80,	/* B1phz */
	0,	/* A2 */
	200,	/* B2phz */
	0,	/* A3 */
	350,	/* B3phz */
	0,	/* A4 */
	500,	/* B4phz */
	0,	/* A5 */
	600,	/* B5phz */
	0,	/* A6 */
	800,	/* B6phz */
	0,	/* ANP */
	0,	/* AB */
	0,	/* AVpdb */
	66	/* Gain0 */
};



typedef struct frame_ty frame_ty;
struct frame_ty
{
	short	f0;	
	short	f1;	
	short	f2;	
	short	f3;	
	short	f4;
	short	f5;
	short	f6;			
	short	bw1;	
	short	bw2;	
	short	bw3;
	short	bw4;
	short	bw5;
	short	bw6;		
	short	fnz;	
	short	fnp;	
	short	av;	
	short	anp;	
	short	asp;	
	short	af;	
	short	a1;	
	short	a2;	
	short	a3;	
	short	a4;	
	short	a5;	
	short	a6;	
	short	ab;	
};


#define NUMBER_OF_SAMPLES 100
#define SAMPLE_FACTOR 0.00001


typedef enum { false, true } bool;

int  read_frames(char *filename); //klatt frames from file
void write_wav(char* infile_par, char* outfile_wav); //using klatt frames readin

//older methods
void frame_read(char *filename, char **data, long *datalen);
void frame_write(char *filename, char *data, long datalen);

//write klatt frames out
void frame_write_klatt(char	*filename,char	*data, long	datalen);

void frame_out(frame_ty	*fp);
void frame_out_collect(char	**out_p, long *outlen_p);

pars_ty convert_frame_to_par(frame_ty frame);

klatt_frame_t convert_frame_to_klatt_frame(frame_ty frame);
void print_kframe_data(klatt_frame_t kframe);
void print_kframe_data1(klatt_frame_t kframe);
void print_kframe_data_ptr(klatt_frame_ptr kframe_ptr);


void print_par_data(pars_ty par);
void print_par_data2(pars_ty par);
void print_frame_data(frame_ty frame);




#endif /* FRAME_H */
