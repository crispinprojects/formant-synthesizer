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
 *
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
 * MANIFEST: functions to manipulate parameter frames
 */

#include "frame.h"
#include "mem.h"

static	frame_ty	*list;  //define list
static	long		list_pos;
static	long		list_max;

static int calc_width (int);
static int frame_read_one(FILE *fp, char *filename);



void frame_out(frame_ty	*fp)	
{
	if (list_pos >= list_max) //list is a pointer to a frame_ty
	{
		size_t	nbytes;

		list_max += (1L << 10);
		nbytes = list_max * sizeof(frame_ty);
		if (!list)
			list = (frame_ty *)mem_alloc(nbytes);
		else
			mem_change_size((char **)&list, nbytes);
	}
	list[list_pos++] = *fp;
}


void frame_out_collect(char	**out_p, long *outlen_p)
	
{
	if (list)
	{
		size_t	nbytes;

		nbytes = list_pos * sizeof(frame_ty);
		if (list_pos < list_max)
			mem_change_size((char **)&list, nbytes);
		*out_p = (char *)list;
		*outlen_p = nbytes;
	}
	else
	{
		*out_p = 0;
		*outlen_p = 0;
	}
	list = 0;
	list_max = 0;
	list_pos = 0;
}


static int calc_width(int n)	
{
	int	result;

	if (!n)
		return 1;
	if (n < 0)
	{
		result = 1;
		n = -n;
	}
	else
		result = 0;
	while (n > 0)
	{
		n /= 10;
		result++;
	}
	return result;
}


void frame_write(char	*filename,char	*data, long	datalen)	
{       
	int		i;
	FILE		*fp;
	frame_ty	*frame;
	long		frame_count;
	frame_ty	width;

	if (filename)
	{
		fp = fopen(filename, "w");
		if (!fp)
			printf("file open error %s\n",filename);
			
	}
	else
	{
		fp = stdout;
		filename = "(standard output)";
	}
	frame = (frame_ty *)data;
	frame_count = datalen / sizeof(frame_ty);

	/*
	 * compute fields widths
	 */
	width.f0 = 1;
	width.f1 = 1;
	width.f2 = 1;
	width.f3 = 1;
	width.bw1 = 1;
	width.bw2 = 1;
	width.bw3 = 1;
	width.fnz = 1;
	width.fnp = 1;
	width.av = 1;
	width.anp = 1;
	width.asp = 1;
	width.af = 1;
	width.a1 = 1;
	width.a2 = 1;
	width.a3 = 1;
	width.a4 = 1;
	width.a5 = 1;
	width.a6 = 1;
	width.ab = 1;
	for (i = 0; i < frame_count; i++)
	{
		int	w;

#define CWID(xx) w = calc_width(frame[i].xx); if (w > width.xx) width.xx = w;
		CWID(f0);
		CWID(f1);
		CWID(f2);
		CWID(f3);
		CWID(f4);
		CWID(f5);
		CWID(f6);
		
		CWID(bw1);
		CWID(bw2);
		CWID(bw3);
		CWID(bw4);
		CWID(bw5);
		CWID(bw6);
		
		CWID(fnz);
		CWID(fnp);
		CWID(av);
		CWID(anp);
		CWID(asp);
		CWID(af);
		CWID(a1);
		CWID(a2);
		CWID(a3);
		CWID(a4);
		CWID(a5);
		CWID(a6);
		CWID(ab);
#undef CWID
	}

	/*
	 * emit the frames
	 */
	for (i = 0; i < frame_count; i++)
	{
		fprintf
		(
			fp,
"%*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd \
%*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd %*hd\n",
			width.f0, frame[i].f0,
			
			width.f1, frame[i].f1,
			width.f2, frame[i].f2,
			width.f3, frame[i].f3,
			
			width.f4, frame[i].f4,
			width.f5, frame[i].f5,
			width.f6, frame[i].f6,
			
			width.bw1, frame[i].bw1,
			width.bw2, frame[i].bw2,
			width.bw3, frame[i].bw3,
			width.bw4, frame[i].bw4,
			width.bw5, frame[i].bw5,
			width.bw6, frame[i].bw6,
			
			
			width.fnz, frame[i].fnz,
			
			
			width.fnp, frame[i].fnp,
			width.av, frame[i].av,
			width.anp, frame[i].anp,
			width.asp, frame[i].asp,
			width.af, frame[i].af,
			width.a1, frame[i].a1,
			width.a2, frame[i].a2,
			width.a3, frame[i].a3,
			width.a4, frame[i].a4,
			width.a5, frame[i].a5,
			width.a6, frame[i].a6,
			width.ab, frame[i].ab
		);
	}
	if (fflush(fp))
		
		printf("write error %s\n",filename);
	if (fclose(fp))
	
		printf("close error %s\n", filename);
}

void frame_write_klatt(char	*filename,char	*data, long	datalen)	
{       
	int		i;
	FILE		*fp;
	frame_ty	*frame;
	long		frame_count;
	frame_ty	width;

	if (filename)
	{
		fp = fopen(filename, "w");
		if (!fp)
			printf("file open error %s\n",filename);
			
	}
	else
	{
		fp = stdout;
		filename = "(standard output)";
	}
	frame = (frame_ty *)data;
	frame_count = datalen / sizeof(frame_ty);

   klatt_frame_t kframe;
 

	/*
	 * emit the frames
	 */
	for (i = 0; i < frame_count; i++)
	{
	kframe = convert_frame_to_klatt_frame(frame[i]);

	fprintf(fp, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",
	
	kframe.F0hz10,       
	kframe.AVdb,       
	kframe.F1hz,        
	kframe.B1hz,        
	kframe.F2hz,       
	kframe.B2hz,      
	kframe.F3hz,       
	kframe.B3hz,     
	kframe.F4hz,        
	kframe.B4hz,      
	kframe.F5hz,        
	kframe.B5hz,       
	kframe.F6hz,      
	kframe.B6hz,     
	kframe.FNZhz,     
	kframe.BNZhz,       
	kframe.FNPhz,      
	kframe.BNPhz,      
	kframe.ASP,     
	kframe.Kopen,     
	kframe.Aturb,     
	kframe.TLTdb,      
	kframe.AF,       
	kframe.Kskew,
	kframe.A1,       
	kframe.B1phz,        
	kframe.A2,        
	kframe.B2phz,       
	kframe.A3,       
	kframe.B3phz,       
	kframe.A4,     
	kframe.B4phz,       
	kframe.A5,       
	kframe.B5phz,       
	kframe.A6,       
	kframe.B6phz,       
	kframe.ANP,      
	kframe.AB,      
	kframe.AVpdb,       
	kframe.Gain0); 
		
	}
	if (fflush(fp))
		//nfatal("write \"%s\"", filename);
		printf("write error %s\n",filename);
	if (fclose(fp))
		//nfatal("close \"%s\"", filename);
		printf("close error %s\n", filename);
}



static int frame_read_one(FILE *fp, char *filename)	
{
	frame_ty	frame;
	int		n;

	n =
		fscanf
		(
			fp,
		"%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd%hd",
			&frame.f0,
			
			&frame.f1,
			&frame.f2,
			&frame.f3,	
			&frame.f4,
			&frame.f5,
			&frame.f6,
			
			&frame.bw1,
			&frame.bw2,
			&frame.bw3,
			&frame.bw4,
			&frame.bw5,
			&frame.bw6,
			
			
			&frame.fnz,
			&frame.fnp,
			&frame.av,
			&frame.anp,
			&frame.asp,
			&frame.af,
			&frame.a1,
			&frame.a2,
			&frame.a3,
			&frame.a4,
			&frame.a5,
			&frame.a6,
			&frame.ab
		);
	if (n != 20)
	{
		if (ferror(fp))
			//nfatal("read \"%s\"", filename);
			printf("read error %s\n",filename);
		if (n != EOF)
			//fatal("%s: format error", filename);
			printf("format error %s\n", filename);
		return 0;
	}
	frame_out(&frame);
	return 1;
}


void frame_read(char *filename, char **data, long *datalen)
{
	FILE	*fp;

	if (filename)
	{
		fp = fopen(filename, "r");
		if (!fp)
			//nfatal("open \"%s\"", filename);
			printf("frame read open error %s\n",filename);
	}
	else
	{
		fp = stdin;
		filename = "(standard input)";
	}
	while (frame_read_one(fp, filename))
		;
	if (fclose(fp))
		//nfatal("close \"%s\"", filename);
		printf("frame read close error %s\n",filename);
	frame_out_collect(data, datalen);
}
 
klatt_frame_t convert_frame_to_klatt_frame(frame_ty frame){
	
	klatt_frame_t kframe;
	
	//kframe.F0hz10= (long)frame.f0; /* Voicing fund freq in Hz */  
	kframe.F0hz10= 800; /* Voicing fund freq in Hz */       
	kframe.AVdb = (long)frame.av;  /* Amp of voicing in dB, 0 to 70  */          
	kframe.F1hz= (long) frame.f1;  /* First formant freq in Hz,   200 to 1300  */       
	kframe.B1hz = (long)frame.bw1; /* First formant bw in Hz,          40 to 1000      */        
	kframe.F2hz= (long)frame.f2;  /* Second formant freq in Hz,       550 to 3000     */      
	kframe.B2hz =(long)frame.bw2;  /* Second formant bw in Hz,         40 to 1000      */    
	kframe.F3hz =(long) frame.f3;   /* Third formant freq in Hz,        1200 to 4999    */     
	kframe.B3hz =(long)frame.bw3;   /* Third formant bw in Hz,          40 to 1000      */     
	kframe.F4hz=(long)frame.f4;  /* Fourth formant freq in Hz,       1200 to 4999  3250  */       
	kframe.B4hz=(long)frame.bw4;     /* Fourth formant bw in Hz,         40 to 1000   200   */   
	kframe.F5hz=(long) frame.f5;  /* Fifth formant freq in Hz,        1200 to 4999  3700  */      
	kframe.B5hz=(long)frame.bw5;   /* Fifth formant bw in Hz,          40 to 1000    200  */     
	kframe.F6hz=(long) frame.f6; /* Sixth formant freq in Hz,        1200 to 4999  4990  */       
	kframe.B6hz=(long)frame.bw6;   /* Nasal zero freq in Hz,           248 to  528   500  */   
	kframe.FNZhz=(long)frame.fnz; /* Nasal zero freq in Hz,           248 to  528     */      
	kframe.BNZhz=0;  /* Nasal zero bw in Hz,             40 to 1000    50  */        
	kframe.FNPhz=200;  /* Nasal pole freq in Hz,           248 to  528   250  */        
	kframe.BNPhz=40;  /* Nasal pole bw in Hz,             40 to 1000     280 */        
	kframe.ASP=(long)frame.asp;  /* Amp of aspiration in dB,         0 to   70       */          
	kframe.Kopen=30;  /* # of samples in open period,     10 to   65      */        
	kframe.Aturb=0;  /* Breathiness in voicing,          0 to   80    e.g.40   */        
	kframe.TLTdb=0;  /* Voicing spectral tilt in dB,     0 to   24    e.g. 10  */        
	kframe.AF= (long)frame.af;  /* Amp of frication in dB,          0 to   80       */       
	kframe.Kskew =0;  /* Skewness of alternate periods,   0 to   40 in sample#/2  */
	kframe.A1=(long)frame.a1;  /* Amp of par 1st formant in dB,    0 to   80       */      
	kframe.B1phz =52; /* Par. 1st formant bw in Hz,       40 to 1000     200 */        
	kframe.A2=(long)frame.a2; /* Amp of F2 frication in dB,       0 to   80       */       
	kframe.B2phz =56; /* Par. 2nd formant bw in Hz,       40 to 1000     350 */        
	kframe.A3=(long)frame.a3;  /* Amp of F3 frication in dB,       0 to   80       */     
	kframe.B3phz=71;  /* Par. 3rd formant bw in Hz,       40 to 1000     500 */        
	kframe.A4=(long)frame.a4; /* Amp of F4 frication in dB,       0 to   80       */      
	kframe.B4phz=66;  /* Par. 4th formant bw in Hz,       40 to 1000    600  */        
	kframe.A5=(long)frame.a5;  /* Amp of F5 frication in dB,       0 to   80       */      
	kframe.B5phz=80;  /* Par. 5th formant bw in Hz,       40 to 1000      */        
	kframe.A6=(long)frame.a6;   /* Amp of F6 frication in dB,       0 to   80       */     
	kframe.B6phz =80;  /* Par. 6th formant bw in Hz,       40 to 2000    800  */        
	kframe.ANP=(long)frame.anp; /* Amp of par nasal pole in dB,     0 to   80       */      
	kframe.AB=(long)frame.ab;  /* Amp of bypass fric. in dB,       0 to   80       */      
	kframe.AVpdb =60;  /* Amp of voicing,  par in dB,      0 to   70    e.g. 40   */        
	kframe.Gain0=60;  /* Overall gain, 60 dB is unity,    0 to   60       */  
	
	return kframe;
}


void print_kframe_data1(klatt_frame_t kframe) {
	
	printf("fo=%i av=%i f1=%i b1=%i f2=%i b2=%i f3=%i b3=%i f4=%i b4=%i f5=%i b5=%i f6=%i b6=%i fnz=%i bnz=%i fnp=%i bnp=%i asp=%i kopen=%i aturb=%i tlt=%i af=%i kskew=%i a1=%i b1=%i a2=%i b2=%i a3=%i b3=%i a4=%i b4=%i a5=%i b5=%i a6=%i b6=%i anp=%i ab=%i avp=%i gain=%i\n",
	
	kframe.F0hz10,       
	kframe.AVdb,       
	kframe.F1hz,        
	kframe.B1hz,        
	kframe.F2hz,       
	kframe.B2hz,      
	kframe.F3hz,       
	kframe.B3hz,     
	kframe.F4hz,        
	kframe.B4hz,      
	kframe.F5hz,        
	kframe.B5hz,       
	kframe.F6hz,      
	kframe.B6hz,     
	kframe.FNZhz,     
	kframe.BNZhz,       
	kframe.FNPhz,      
	kframe.BNPhz,      
	kframe.ASP,     
	kframe.Kopen,     
	kframe.Aturb,     
	kframe.TLTdb,      
	kframe.AF,       
	kframe.Kskew,
	kframe.A1,       
	kframe.B1phz,        
	kframe.A2,        
	kframe.B2phz,       
	kframe.A3,       
	kframe.B3phz,       
	kframe.A4,     
	kframe.B4phz,       
	kframe.A5,       
	kframe.B5phz,       
	kframe.A6,       
	kframe.B6phz,       
	kframe.ANP,      
	kframe.AB,      
	kframe.AVpdb,       
	kframe.Gain0); 
	
	
}

void print_kframe_data(klatt_frame_t kframe) {
	
	printf("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",
	
	kframe.F0hz10,       
	kframe.AVdb,       
	kframe.F1hz,        
	kframe.B1hz,        
	kframe.F2hz,       
	kframe.B2hz,      
	kframe.F3hz,       
	kframe.B3hz,     
	kframe.F4hz,        
	kframe.B4hz,      
	kframe.F5hz,        
	kframe.B5hz,       
	kframe.F6hz,      
	kframe.B6hz,     
	kframe.FNZhz,     
	kframe.BNZhz,       
	kframe.FNPhz,      
	kframe.BNPhz,      
	kframe.ASP,     
	kframe.Kopen,     
	kframe.Aturb,     
	kframe.TLTdb,      
	kframe.AF,       
	kframe.Kskew,
	kframe.A1,       
	kframe.B1phz,        
	kframe.A2,        
	kframe.B2phz,       
	kframe.A3,       
	kframe.B3phz,       
	kframe.A4,     
	kframe.B4phz,       
	kframe.A5,       
	kframe.B5phz,       
	kframe.A6,       
	kframe.B6phz,       
	kframe.ANP,      
	kframe.AB,      
	kframe.AVpdb,       
	kframe.Gain0); 
	
	
}


pars_ty convert_frame_to_par(frame_ty frame){
	
	pars_ty	 par;
	
	par = def_pars;
	
	par.F0hz10 = frame.f0;
	par.F1hz = frame.f1;
	par.F2hz = frame.f2;
	par.F3hz = frame.f3;
	par.B1hz = frame.bw1;
	par.B2hz = frame.bw2;
	par.B3hz = frame.bw3;
	par.FNZhz = frame.fnz;
	par.FNPhz = frame.fnp;
	par.AVdb = frame.av;
	//par.TLTdb = fp->anp; */
	par.ANP = frame.anp;
	par.AP = frame.asp;
	par.AF = frame.af;
	par.A1 = frame.a1;
	par.A2 = frame.a2;
	par.A3 = frame.a3;
	par.A4 = frame.a4;
	par.A5 = frame.a5;
	par.A6 = frame.a6;
	par.AB = frame.ab;
	
	return par;
}



void print_frame_data(frame_ty frame) {
	//printf("print frame data\n");
	printf("f0 =%i f1=%i f2=%i f3=%i f4=%i f5=%i f6=%i bw1=%i bw2=%i bw3=%i bw4=%i bw5=%i bw6=%i fnz=%i fnp=%i av=%i anp=%i asp=%i af=%i a1=%i a2=%i a3=%i a4=%i a5=%i a6=%i ab=%i\n",		
	frame.f0,
	
	frame.f1,
	frame.f2,
	frame.f3,
	frame.f4,
	frame.f5,
	frame.f6,
	
	frame.bw1,
	frame.bw2,
	frame.bw3,
	frame.bw4,
	frame.bw5,
	frame.bw6,
	
	frame.fnz,
	frame.fnp,
	frame.av,
	frame.anp,
	frame.asp,
	frame.af,
	frame.a1,
	frame.a2,
	frame.a3,
	frame.a4,
	frame.a5,
	frame.a6,
	frame.ab);
}

void print_par_data(pars_ty par) {
	
	printf("f0 =%i av=%i f1=%i b1=%i f2=%i b2=%i f3=%i b3=%i f4=%i b4=%i f5=%i b5=%i f6=%i b6=%i\
	fnz=%i bnz=%i fnp=%i bnp=%i ap=%i kopen=%i aturb=%i tlt=%i af=%i kskew=%i\
	a1=%i b1=%i a2=%i b2=%i a3=%i b3=%i a4=%i b4=%i a5=%i b5=%i a6=%i b6=%i avp=%i gain=%i\n",
	par.F0hz10,
	par.AVdb,
	par.F1hz,
	par.B1hz,
	par.F2hz,
	par.B2hz,
	par.F3hz,
	par.B3hz,
	par.F4hz,
	par.B4hz,
	par.F5hz,
	par.B5hz,
	par.F6hz,
	par.B6hz,
	par.FNZhz,
	par.BNZhz,
	par.FNPhz,
	par.BNPhz,
	par.AP,
	par.Kopen,
	par.Aturb,
	par.TLTdb,
	par.AF,
	par.Kskew,
	par.A1,
	par.B1phz,
	par.A2,
	par.B2phz,
	par.A3,
	par.B3phz,
	par.A4,
	par.B4phz,
	par.A5,
	par.B5phz,
	par.A6,
	par.B6phz,
	par.ANP,
	par.AB,
	par.AVpdb,
	par.Gain0);	
}


void print_par_data2(pars_ty par) {
	
	printf("%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i\n",
	par.F0hz10,
	par.AVdb,
	par.F1hz,
	par.B1hz,
	par.F2hz,
	par.B2hz,
	par.F3hz,
	par.B3hz,
	par.F4hz,
	par.B4hz,
	par.F5hz,
	par.B5hz,
	par.F6hz,
	par.B6hz,
	par.FNZhz,
	par.BNZhz,
	par.FNPhz,
	par.BNPhz,
	par.AP,
	par.Kopen,
	par.Aturb,
	par.TLTdb,
	par.AF,
	par.Kskew,
	par.A1,
	par.B1phz,
	par.A2,
	par.B2phz,
	par.A3,
	par.B3phz,
	par.A4,
	par.B4phz,
	par.A5,
	par.B5phz,
	par.A6,
	par.B6phz,
	par.ANP,
	par.AB,
	par.AVpdb,
	par.Gain0);	
}
//---------------------------------------------------------------

void print_kframe_data_ptr(klatt_frame_ptr kframe_ptr){
	printf("print klatt frame using ptr\n");
}



int read_frames(char *filename) {
	
	FILE *infp;
	char infile[80];
	klatt_frame_ptr  frame;
	bool done_flag = false;
	int result;
	
	strcpy(infile,filename);
	infp = fopen(infile,"r");
	if (infp == NULL)
	{
	perror("can't open input file");
	return 1;
	}
		
	frame = (klatt_frame_ptr)malloc(sizeof(klatt_frame_t));
		
	if (frame == NULL)
	{
		perror("frame malloc failed");
		return 1;
	}
	
			
	while(done_flag == false)
	{
		result = fscanf(infp,
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 0x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 1x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 2x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", /* 3x */
		                &frame->F0hz10, &frame->AVdb,
		                &frame->F1hz,   &frame->B1hz,
		                &frame->F2hz,   &frame->B2hz,
		                &frame->F3hz,   &frame->B3hz,
		                &frame->F4hz,   &frame->B4hz,
		                &frame->F5hz,   &frame->B5hz,
		                &frame->F6hz,   &frame->B6hz,
		                &frame->FNZhz,  &frame->BNZhz,
		                &frame->FNPhz,  &frame->BNPhz,
		                &frame->ASP,    &frame->Kopen,
		                &frame->Aturb,  &frame->TLTdb,
		                &frame->AF,     &frame->Kskew,
		                &frame->A1,     &frame->B1phz,
		                &frame->A2,     &frame->B2phz,
		                &frame->A3,     &frame->B3phz,
		                &frame->A4,     &frame->B4phz,
		                &frame->A5,     &frame->B5phz,
		                &frame->A6,     &frame->B6phz,
		                &frame->ANP,    &frame->AB,
		                &frame->AVpdb,  &frame->Gain0);

		if (result == EOF) 	done_flag = true;
		else print_kframe_data_ptr(frame);             //print_frame_data(frame);
		
		
		} //while

	if (*infile)
		fclose(infp);

	return 0;
	
}



void write_wav(char* infile_par, char* outfile_wav){
	
		
	FILE *infp;
	FILE *outfp;
	char infile[80];
	char outfile[80];
	
	klatt_frame_ptr  frame;	
	klatt_global_ptr globals;
	
	int *iwave;
	int isam;
	int icount=0;
	int nmspf_def;
	
	bool done_flag = false;
	
	//raw wav output parameters
	unsigned char high_byte;
	unsigned char low_byte;
	bool raw_flag =true;
	int raw_type=2; //low byte preceeds high byte
	
	
	int result;
	
	//set input file
	strcpy(infile,infile_par);
	infp = fopen(infile,"r");
	if (infp == NULL)
	{
	perror("can not open input file");
	return;
	}
	//set output file
	strcpy(outfile, outfile_wav);	
	outfp = fopen(outfile,"w");
	if (outfp == NULL)
	{
	perror("can not open output file");
	return;
	}	
	
	
	//klatt natural samples long
	static int natural_samples2[256] = {
	 2583,  2516,  2450,  2384,  2319,  2254,  2191,  2127,
	 2067,  2005,  1946,  1890,  1832,  1779,  1726,  1675,
	 1626,  1579,  1533,  1491,  1449,  1409,  1372,  1336,
	 1302,  1271,  1239,  1211,  1184,  1158,  1134,  1111,
	 1089,  1069,  1049,  1031,  1013,   996,   980,   965,
	  950,   936,   921,   909,   895,   881,   869,   855,
	  843,   830,   818,   804,   792,   779,   766,   754,
	  740,   728,   715,   702,   689,   676,   663,   651,
	  637,   626,   612,   601,   588,   576,   564,   552,
	  540,   530,   517,   507,   496,   485,   475,   464,
	  454,   443,   434,   424,   414,   404,   394,   385,
	  375,   366,   355,   347,   336,   328,   317,   308,
	  299,   288,   280,   269,   260,   250,   240,   231,
	  220,   212,   200,   192,   181,   172,   161,   152,
	  142,   133,   123,   113,   105,    94,    86,    76,
	   67,    57,    49,    39,    30,    22,    11,     4,
	   -5,   -14,   -23,   -32,   -41,   -50,   -60,   -69,
	  -78,   -87,   -96,  -107,  -115,  -126,  -134,  -144,
	 -154,  -164,  -174,  -183,  -193,  -203,  -213,  -222,
	 -233,  -242,  -252,  -262,  -271,  -281,  -291,  -301,
	 -310,  -320,  -330,  -339,  -349,  -357,  -368,  -377,
	 -387,  -397,  -406,  -417,  -426,  -436,  -446,  -456,
	 -467,  -477,  -487,  -499,  -509,  -521,  -532,  -543,
	 -555,  -567,  -579,  -591,  -603,  -616,  -628,  -641,
	 -653,  -666,  -679,  -692,  -705,  -717,  -732,  -743,
	 -758,  -769,  -783,  -795,  -808,  -820,  -834,  -845,
	 -860,  -872,  -885,  -898,  -911,  -926,  -939,  -955,
	 -968,  -986,  -999, -1018, -1034, -1054, -1072, -1094,
	-1115, -1138, -1162, -1188, -1215, -1244, -1274, -1307,
	-1340, -1377, -1415, -1453, -1496, -1538, -1584, -1631,
	-1680, -1732, -1783, -1839, -1894, -1952, -2010, -2072,
	-2133, -2196, -2260, -2325, -2390, -2456, -2522, -2589,
};
	
	
	
	//klatt natural samples
	static int natural_samples[NUMBER_OF_SAMPLES]=
	{
		 -310,  -400,   530,   356,   224,    89,   23,  -10, -58, -16, 461,  599,  536,   701,   770,
		  605,   497,   461,   560,   404,   110,  224,  131, 104, -97, 155,  278, -154, -1165,
		 -598,   737,   125,  -592,    41,    11, -247,  -10,  65,  92,  80, -304,   71,   167,    -1, 122,
		  233,   161,   -43,   278,   479,   485,  407,  266, 650, 134,  80,  236,   68,   260,   269, 179,
		   53,   140,   275,   293,   296,   104,  257,  152, 311, 182, 263,  245,  125,   314,   140, 44,
		  203,   230,  -235,  -286,    23,   107,   92,  -91,  38, 464, 443,  176,   98,  -784, -2449,
		-1891, -1045, -1600, -1462, -1384, -1261, -949, -730
	};
	
	//set klatt global parameters
	globals = (klatt_global_ptr)malloc(sizeof(klatt_global_t));
	if (globals == NULL)
	{
		perror("malloc failed");
		return;
	}
	
	//globals->quiet_flag = TRUE;
	globals->synthesis_model = CASCADE_PARALLEL;
	globals->nfcascade = 0;	
	globals->samrate = 10000;
	globals->glsource = NATURAL; // IMPULSIVE 0,NATURAL 1,SAMPLED 2,
	globals->natural_samples = natural_samples2;	
	globals->num_samples = NUMBER_OF_SAMPLES;	
	globals->sample_factor = (float) SAMPLE_FACTOR;	
	nmspf_def = 10;		
	globals->f0_flutter = 5;	
	
	raw_flag = true;
	raw_type = 2; 
	
	globals->nspfr = (globals->samrate * nmspf_def) / 1000;	
	
	//allocate frame memory	
	frame = (klatt_frame_ptr)malloc(sizeof(klatt_frame_t));		
	if (frame == NULL)
	{
		perror("frame malloc failed");
		return;
	}
	
	//allocate wave file memory
	iwave = (int*) malloc(sizeof(int)*MAX_SAM);	
	if (iwave == NULL)
	{
		perror("malloc failed");
		return;
	}
	
	icount=0;	
	parwave_init(globals);
			
	while(done_flag == false)
	{
		result = fscanf(infp,
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 0x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 1x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld " /* 2x */
		                "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", /* 3x */
		                &frame->F0hz10, &frame->AVdb,
		                &frame->F1hz,   &frame->B1hz,
		                &frame->F2hz,   &frame->B2hz,
		                &frame->F3hz,   &frame->B3hz,
		                &frame->F4hz,   &frame->B4hz,
		                &frame->F5hz,   &frame->B5hz,
		                &frame->F6hz,   &frame->B6hz,
		                &frame->FNZhz,  &frame->BNZhz,
		                &frame->FNPhz,  &frame->BNPhz,
		                &frame->ASP,    &frame->Kopen,
		                &frame->Aturb,  &frame->TLTdb,
		                &frame->AF,     &frame->Kskew,
		                &frame->A1,     &frame->B1phz,
		                &frame->A2,     &frame->B2phz,
		                &frame->A3,     &frame->B3phz,
		                &frame->A4,     &frame->B4phz,
		                &frame->A5,     &frame->B5phz,
		                &frame->A6,     &frame->B6phz,
		                &frame->ANP,    &frame->AB,
		                &frame->AVpdb,  &frame->Gain0);

		if (result == EOF) 	done_flag = true;
		else {
		//print_frame_data(frame);
		parwave(globals,frame,iwave);
		
		//if (globals->quiet_flag == FALSE)
			//{l
				//fflush(stdout);
				//fprintf(stderr, "\rFrame %i",icount);
				//fflush(stderr);
			//}
		
		
		for (isam = 0; isam < globals->nspfr; ++isam)
			{
				if (raw_flag == true)
				{
					low_byte = iwave[isam] & 0xff;
					high_byte = iwave[isam] >> 8;

					if (raw_type == 1)
						fprintf(outfp,"%c%c",high_byte,low_byte);
					else
						fprintf(outfp,"%c%c",low_byte,high_byte);
				}
				else
					fprintf(outfp,"%i\n",iwave[isam]);
			}
			icount++;
		
		
	    }
		
		
		} //while

	if (*infile)
		fclose(infp);

    if (*outfile)
		fclose(outfp);
	
	return;
	
}

