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
 * MANIFEST: functions to conver phonmes to klatt
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#include "features.h"
#include "fricatives.h"
#include "phonemes.h"
#include "plosives.h"
#include "rules.h"
#include "sonorants.h"
#include "vowel.h"
#include "var.h"
#include "mem.h"


static	char	*get_byte_data;
static	long	get_byte_pos;
static	long	get_byte_len;


#define THE_END -256
#define SINGLE(a) ((long)(a))
#define PAIR(a, b) ((long)(a) | ((long)(b) << 8))
#define TRIPPLE(a, b, c) ((long)(a) | ((long)(b) << 8) | ((long)(c) << 16))
#define QUAD(a, b, c, d) ((long)(a) | ((long)(b) << 8) | ((long)(c) << 16) | ((long)(d) << 24))


static int get_byte (void);
static void get_byte_undo(void);
static segment_ty get_phoneme (void);
static void gen_pause (void);
static int set_params (int type, int off, int next_phone);

static int get_byte()
{
	if (get_byte_pos >= get_byte_len)
		return THE_END;
	return (unsigned char)get_byte_data[get_byte_pos++];
}



static void get_byte_undo()
{
	if (get_byte_pos > 0)
		--get_byte_pos;
}

static segment_ty get_phoneme()
{
	int		cc;
	char		c[4];
	segment_ty	result;
	int		n;

	printf("calling get_phoneme()\n");
	for (n = 0; n < SIZEOF(c); ++n)
		c[n] = 0;
	cc = get_byte();
	if (cc == THE_END)
	{
		result.phone = THE_END;
		result.duration = 0;
		goto done;
	}
	if (islower(cc))
		c[0] = toupper(cc);
	else if (isupper(cc))
	{
		c[0] = cc;
		cc = get_byte();
		if (cc != THE_END)
		{
			if (islower(cc))
				cc = toupper(cc);
			c[1] = cc;
		}
	}
	else if (cc == '('/*)*/)
	{
		for (n = 0; ; ++n)
		{
			cc = get_byte();
			if (cc == THE_END)
				break;
			if (cc == /*(*/')')
				break;
			if (islower(cc))
				cc = toupper(cc);
			if (n < SIZEOF(c))
				c[n] = cc;
		}
	}
	else
		c[0] = cc;
	switch (QUAD(c[0], c[1], c[2], c[3]))
	{
	case SINGLE('A'):
	case PAIR('A', 'A'):
	case PAIR('O', 'H'):
		result.phone = AA; break;
	case PAIR('A', 'E'): result.phone = AE; break;
	case PAIR('A', 'H'): result.phone = AH; break;
	case PAIR('A', 'O'): result.phone = AO; break;
	case PAIR('A', 'W'): result.phone = AW; break;
	case PAIR('A', 'X'): result.phone = AX; break;
	case TRIPPLE('A', 'X', 'R'): result.phone = AXR; break;
	case PAIR('A', 'Y'): result.phone = AY; break;

	case SINGLE('B'): result.phone = BB; break;
	case PAIR('B', 'B'): result.phone = BB; break;

	case PAIR('C', 'H'): result.phone = CH; break;

	case SINGLE('D'): result.phone = DD; break;
	case PAIR('D', 'D'): result.phone = DD; break;
	case PAIR('D', 'H'): result.phone = DH; break;
	case PAIR('D', 'X'): result.phone = DX; break;

	case PAIR('E', 'H'): result.phone = EH; break;
	case PAIR('E', 'L'): result.phone = EL; break;
	case PAIR('E', 'M'): result.phone = EM; break;
	case PAIR('E', 'N'): result.phone = EN; break;
	case PAIR('E', 'R'): result.phone = ER; break;
	case TRIPPLE('E', 'X', 'R'): result.phone = EXR; break;
	case PAIR('E', 'Y'): result.phone = EY; break;

	case SINGLE('F'): result.phone = FF; break;
	case PAIR('F', 'F'): result.phone = FF; break;

	case SINGLE('G'): result.phone = GG; break;
	case PAIR('G', 'G'): result.phone = GG; break;
	case PAIR('G', 'P'): result.phone = GP; break;

	case SINGLE('H'): result.phone = HH; break;
	case PAIR('H', 'H'): result.phone = HH; break;
	case PAIR('H', 'X'): result.phone = HX; break;

	case PAIR('I', 'H'): result.phone = IH; break;
	case PAIR('I', 'X'): result.phone = IX; break;
	case TRIPPLE('I', 'X', 'R'): result.phone = IXR; break;
	case PAIR('I', 'Y'): result.phone = IY; break;

	case SINGLE('J'): result.phone = JJ; break;
	case PAIR('J', 'J'): result.phone = JJ; break;

	case SINGLE('K'): result.phone = KK; break;
	case PAIR('K', 'K'): result.phone = KK; break;
	case PAIR('K', 'P'): result.phone = KP; break;

	case SINGLE('L'): result.phone = LL; break;
	case PAIR('L', 'L'): result.phone = LL; break;
	case PAIR('L', 'X'): result.phone = LX; break;

	case SINGLE('M'): result.phone = MM; break;
	case PAIR('M', 'M'): result.phone = MM; break;

	case PAIR('N', 'G'): result.phone = NG; break;
	case SINGLE('N'): result.phone = NN; break;
	case PAIR('N', 'N'): result.phone = NN; break;

	case PAIR('O', 'W'): result.phone = OW; break;
	case TRIPPLE('O', 'X', 'R'): result.phone = OXR; break;
	case PAIR('O', 'Y'): result.phone = OY; break;

	case SINGLE('P'): result.phone = PP; break;
	case PAIR('P', 'P'): result.phone = PP; break;

	case SINGLE('R'): result.phone = RR; break;
	case PAIR('R', 'R'): result.phone = RR; break;
	case PAIR('R', 'X'): result.phone = RX; break;

	case SINGLE('S'): result.phone = SS; break;
	case PAIR('S', 'H'): result.phone = SH; break;
	case PAIR('S', 'S'): result.phone = SS; break;
		
	case SINGLE('T'): result.phone = TT; break;
	case PAIR('T', 'H'): result.phone = TH; break;
	case PAIR('T', 'Q'): result.phone = TQ; break;
	case PAIR('T', 'T'): result.phone = TT; break;

	case PAIR('U', 'H'): result.phone = UH; break;
	case PAIR('U', 'W'): result.phone = UW; break;
	case TRIPPLE('U', 'X', 'R'): result.phone = UXR; break;

	case SINGLE('V'): result.phone = VV; break;
	case PAIR('V', 'V'): result.phone = VV; break;

	case SINGLE('W'): result.phone = WW; break;
	case PAIR('W', 'H'): result.phone = WH; break;
	case PAIR('W', 'W'): result.phone = WW; break;

	case SINGLE('Y'): result.phone = YY; break;
	case PAIR('Y', 'U'): result.phone = YU; break;
	case PAIR('Y', 'Y'): result.phone = YY; break;

	case SINGLE('Z'): result.phone = ZZ; break;
	case PAIR('Z', 'H'): result.phone = ZH; break;
	case PAIR('Z', 'Z'): result.phone = ZZ; break;

	case SINGLE(' '):
	case SINGLE('\t'):
	case SINGLE('\n'):
		result.phone = WORD_BREAK;
		result.duration = 1;
		goto done;

	case SINGLE(','):
		result.phone = WORD_BREAK;
		result.duration = 2;
		goto done;

	case SINGLE('-'):
		result.phone = WORD_BREAK;
		result.duration = 3;
		goto done;

	case SINGLE('.'):
		result.phone = WORD_BREAK;
		result.duration = 4;
		goto done;

	default:
		
		printf("get_phoneme - unknown\n");
		result.phone = THE_END;
		result.duration = 0;
		goto done;
	}
	cc = get_byte();
	if (cc == THE_END)
		result.duration = 1;
	else if (isdigit(cc))
		result.duration = cc - '0' + 1;
	else
	{
		get_byte_undo();
		result.duration = 1;
	}
	done:
	printf("get_phoneme: return %s;  %d\n", phonemes_name(result.phone),
		result.duration);
	
	return result;
}




static void gen_pause()
{
	int		k;
	static frame_ty	frame =
		{ 100, 100, 200, 300, 100, 200, 300, 200, 200, };

	for (k = 0; k < 50; k++)
		frame_out(&frame);
}


/*
 * the following looks up initial values for each of the parameters in the
 * database.  If the phoneme is a vowel with a dipthong, f[1] is filled with
 * the dipthong target.  Otherwise, f[1] = f[0].
 */



static int set_params(int type, int off, int next_phone)
{
	int	return_val = 0;

	printf("set_params(type = %s, off = %d, next_phone = %s)\n",
		phonemes_type_name(type), off, phonemes_name(next_phone));
	fnp = 250;
	fnz = 250;
	
	switch (type)
	{
	case VOWEL_TYPE:
		asp = ab = af = 0;
		a1 = a2 = a3 = a4 = a5 = a6 = 60;
		/* START = 0, END = 1 */
		av[0] = Vowels[off][0].av;
		av[1] = Vowels[off][1].av;
		
		f1[0] = Vowels[off][0].f1;
		f1[1] = Vowels[off][1].f1;
		f2[0] = Vowels[off][0].f2;
		f2[1] = Vowels[off][1].f2;
		f3[0] = Vowels[off][0].f3;
		f3[1] = Vowels[off][1].f3;
		f4[0] = Vowels[off][0].f4;
		f4[1] = Vowels[off][1].f4;
		f5[0] = Vowels[off][0].f5;
		f5[1] = Vowels[off][1].f5;
		f6[0] = Vowels[off][0].f6;
		f6[1] = Vowels[off][1].f6;
		
		bw1[0] = Vowels[off][0].bw1;
		bw1[1] = Vowels[off][1].bw1;
		bw2[0] = Vowels[off][0].bw2;
		bw2[1] = Vowels[off][1].bw2;
		bw3[0] = Vowels[off][0].bw3;
		bw3[1] = Vowels[off][1].bw3;
		
		bw4[0] = Vowels[off][0].bw4;
		bw4[1] = Vowels[off][1].bw4;
		bw5[0] = Vowels[off][0].bw5;
		bw5[1] = Vowels[off][1].bw5;
		bw6[0] = Vowels[off][0].bw6;
		bw6[1] = Vowels[off][1].bw6;
		
		
		s_f0 = (f0[1] - f0[0]) / (float) length;
		
		s_f1 = (f1[1] - f1[0]) / (float) length;
		s_f2 = (f2[1] - f2[0]) / (float) length;
		s_f3 = (f3[1] - f3[0]) / (float) length;
		s_f4 = (f4[1] - f4[0]) / (float) length;
		s_f5 = (f5[1] - f5[0]) / (float) length;
		s_f6 = (f6[1] - f6[0]) / (float) length;
		
		
		s_bw1 = (bw1[1] - bw1[0]) / (float) length;
		s_bw2 = (bw2[1] - bw2[0]) / (float) length;
		s_bw3 = (bw3[1] - bw3[0]) / (float) length;
		s_bw4 = (bw4[1] - bw4[0]) / (float) length;
		s_bw5 = (bw5[1] - bw5[0]) / (float) length;
		s_bw6 = (bw6[1] - bw6[0]) / (float) length;
		
		s_av = (av[1] - av[0]) / (float) length;
		
		return_val = 1;
		break;

	case SONORANT_TYPE:
		a1 = a2 = a3 = a4 = a5 = a6 = 60;
		ab = 0;
		af = 0;
		asp = Sonorants[off].asp;
		av[0] = Sonorants[off].av;
		
		f1[0] = Sonorants[off].f1;
		f2[0] = Sonorants[off].f2;
		f3[0] = Sonorants[off].f3;
		f4[0] = Sonorants[off].f4;
		f5[0] = Sonorants[off].f5;
		f6[0] = Sonorants[off].f6;
		
		bw1[0] = Sonorants[off].bw1;
		bw2[0] = Sonorants[off].bw2;
		bw3[0] = Sonorants[off].bw3;
		bw4[0] = Sonorants[off].bw4;
		bw5[0] = Sonorants[off].bw5;
		bw6[0] = Sonorants[off].bw6;
		
		
		fnp = 250.0;
		fnz = 250.0;
		break;

	case NASAL_TYPE:
		a1 = a2 = a3 = a4 = a5 = a6 = 60;
		ab = af = asp = 0;
		av[0] = Nasals[off].av;
		
		f1[0] = Nasals[off].f1;
		f2[0] = Nasals[off].f2;
		f3[0] = Nasals[off].f3;
		f4[0] = Nasals[off].f4;
		f5[0] = Nasals[off].f5;
		f6[0] = Nasals[off].f6;
		
		bw1[0] = Nasals[off].bw1;
		bw2[0] = Nasals[off].bw2;
		bw3[0] = Nasals[off].bw3;
		bw4[0] = Nasals[off].bw4;
		bw5[0] = Nasals[off].bw5;
		bw6[0] = Nasals[off].bw6;
		
		fnp = Nasals[off].fnp;
		fnz = Nasals[off].fnz;
		break;

	case FRICATIVE_TYPE:
		a1 = 0;
		a2 = Fricatives[off].a2;
		a3 = Fricatives[off].a3;
		a4 = Fricatives[off].a4;
		a5 = Fricatives[off].a5;
		a6 = Fricatives[off].a6;
		ab = Fricatives[off].ab;
		
		av[0] = Fricatives[off].av;
		
		f1[0] = Fricatives[off].f1;
		f2[0] = Fricatives[off].f2;
		f3[0] = Fricatives[off].f3;
		f4[0] = Fricatives[off].f4;
		f5[0] = Fricatives[off].f5;
		f6[0] = Fricatives[off].f6;
		
		bw1[0] = Fricatives[off].bw1;
		bw2[0] = Fricatives[off].bw2;
		bw3[0] = Fricatives[off].bw3;
		bw4[0] = Fricatives[off].bw4;
		bw5[0] = Fricatives[off].bw5;
		bw6[0] = Fricatives[off].bw6;
		
		
		asp = Fricatives[off].asp;
		af = Fricatives[off].af;
		break;

	case PLOSIVE_TYPE:
		a1 = 0;
		a2 = Plosives[off].a2;
		a3 = Plosives[off].a3;
		a4 = Plosives[off].a4;
		a5 = Plosives[off].a5;
		a6 = Plosives[off].a6;
		ab = Plosives[off].ab;
		
		av[0] = Plosives[off].av;
		
		f1[0] = Plosives[off].f1;
		f2[0] = Plosives[off].f2;
		f3[0] = Plosives[off].f3;
		f4[0] = Plosives[off].f4;
		f5[0] = Plosives[off].f5;
		f6[0] = Plosives[off].f6;
		
		bw1[0] = Plosives[off].bw1;
		bw2[0] = Plosives[off].bw2;
		bw3[0] = Plosives[off].bw3;
		bw4[0] = Plosives[off].bw4;
		bw5[0] = Plosives[off].bw5;
		bw6[0] = Plosives[off].bw6;
		
		
		asp = Plosives[off].asp;
		af = Plosives[off].af;
		break;

	case AFFRICATE_TYPE:
		a1 = 0;
		a2 = Affricates[off].a2;
		a3 = Affricates[off].a3;
		a4 = Affricates[off].a4;
		a5 = Affricates[off].a5;
		a6 = Affricates[off].a6;
		ab = Affricates[off].ab;
		
		av[0] = Affricates[off].av;
		f1[0] = Affricates[off].f1;
		f2[0] = Affricates[off].f2;
		f3[0] = Affricates[off].f3;
		f4[0] = Affricates[off].f4;
		f5[0] = Affricates[off].f5;
		f6[0] = Affricates[off].f6;
		
		bw1[0] = Affricates[off].bw1;
		bw2[0] = Affricates[off].bw2;
		bw3[0] = Affricates[off].bw3;
		bw4[0] = Affricates[off].bw4;
		bw5[0] = Affricates[off].bw5;
		bw6[0] = Affricates[off].bw6;
		
		
		asp = Affricates[off].asp;
		af = Affricates[off].af;
		break;

	case PSUEDO_VOWEL_TYPE:
		a1 = 0;
		a2 = Psuedo_vowels[off].a2;
		a3 = Psuedo_vowels[off].a3;
		a4 = Psuedo_vowels[off].a4;
		a5 = Psuedo_vowels[off].a5;
		a6 = Psuedo_vowels[off].a6;
		ab = Psuedo_vowels[off].ab;
		
		av[0] = Psuedo_vowels[off].av;
		
		f1[0] = Psuedo_vowels[off].f1;
		f2[0] = Psuedo_vowels[off].f2;
		f3[0] = Psuedo_vowels[off].f3;
		f4[0] = Psuedo_vowels[off].f4;
		f5[0] = Psuedo_vowels[off].f5;
		f6[0] = Psuedo_vowels[off].f6;
		
		bw1[0] = Psuedo_vowels[off].bw1;
		bw2[0] = Psuedo_vowels[off].bw2;
		bw3[0] = Psuedo_vowels[off].bw3;
		bw4[0] = Psuedo_vowels[off].bw4;
		bw5[0] = Psuedo_vowels[off].bw5;
		bw6[0] = Psuedo_vowels[off].bw6;
		
		asp = Psuedo_vowels[off].asp;
		break;

	default:
		printf("unknown type");
	}
	printf("set_params: return %d\n", return_val);
	//trace((/*{*/"}\n"));
	return return_val;
}


void phonemes_to_klatt(char *in, long inlen, char **out_p, long *outlen_p)
{
	long	j;
	long	k;
	int	next_phone;
	int	last_phone;
	int	type;
	int	off;
	int	interp = 0;
	unsigned long features;
	long	i;
	long	new_word;
	long	s_count;
	long	count;
	long	h;
	long	list_count;
	long	ph_list_max;
	long	ph_list_pos;
	segment_ty	*ph_list;
	long	*syll_count;
	long	syll_count_max;
	long	word_count;

	printf("calling phonemes_to_klatt()\n");
	get_byte_data = in;
	get_byte_pos = 0;
	get_byte_len = inlen;

	/*
	 * read the phonemes
	 */
	ph_list_max = (1L << 15);
	ph_list_pos = 0;
	ph_list = (segment_ty *)mem_alloc(ph_list_max * sizeof(segment_ty));
	for (;;)
	{
		segment_ty	p;

		if (ph_list_pos >= ph_list_max)
		{
			ph_list_max += (1L << 15);
			mem_change_size((char **)&ph_list, ph_list_max * sizeof(segment_ty));
		}
		p = get_phoneme();
		if (p.phone == THE_END)
		{
			p.phone = WORD_BREAK;
			p.duration = 1;
			ph_list[ph_list_pos++] = p;
			break;
		}
		ph_list[ph_list_pos++] = p;
	}

	
	if (!ph_list_pos)
	{
		*out_p = 0;
		*outlen_p = 0;
		goto done;
	}
	
	
	count = ph_list_pos;
	a1 = 0;
	/* inital F0 */
	f0[0] = 1300;
	f0[1] = 1300;

	/* calculate the length of each segment */
	
	segdur(ph_list, count);

	/* 
	 * break the input string into words
	 */
	
	syll_count_max = (1L << 13);
	syll_count = (long *)mem_alloc(syll_count_max * sizeof(long));
	word_count = 0;
	s_count = 0;
	for (i = 0; i < count; i++)
	{
		if (ph_list[i].phone == WORD_BREAK)
		{
			if (word_count >= syll_count_max)
			{
				syll_count_max += (1L << 13);
				mem_change_size((char **)&syll_count, syll_count_max * sizeof(long));
			}
			syll_count[word_count++] = s_count;
			s_count = 0;
		}
		else
			s_count++;
	}

	/* generation loop */
	
	h = 0;
	list_count = 0;
	while (h < word_count)
	{
		new_word = 1;
		i = 0;
		while (i < syll_count[h])
		{
			if (i == syll_count[h] - 1 && h == word_count-1)
				f0_change = -1000;
			else 
				f0_change = 0;

			/* translate to array type and offset */
			if (ph_list[list_count].phone == WORD_BREAK)
			{
				list_count++;
				continue;
			}
			//trace(("mark\n"));
			type = translate_phone(ph_list[list_count].phone, &off);
			length = ph_list[list_count].duration / 10;
			interp = 0;
			
			if (i < (syll_count[h]-1))
				interp = set_params(type, off, ph_list[list_count + 1].phone);
			else
				interp = set_params(type, off, -1);
			
			features = Features[ph_list[list_count].phone];
			
			next_phone = -1;
			last_phone = -1;

			/* calculate previous and next phones if they exist */
			if (i < (syll_count[h]-1))
				next_phone = ph_list[list_count + 1].phone;
			if (!new_word)
				last_phone = ph_list[list_count - 1].phone;
			
			/* generate according to phoneme type */
			if (features & PLOSI)
			{
				gen_plosive
				(
					ph_list[list_count].phone,
					ph_list[list_count].duration,
					last_phone,
					next_phone
				);
			}
			else if (features & FRICA)
			{
				gen_fricative
				(
					ph_list[list_count].phone,
					ph_list[list_count].duration,
					last_phone,
					next_phone
				);
			}
			else if (features & VOWEL)
			{
				gen_vowel
				(
					ph_list[list_count].phone,
					ph_list[list_count].duration,
					last_phone,
					next_phone
				);
			}
			else if (features & SONOR)
			{
				gen_sonorant
				(
					ph_list[list_count].phone,
					ph_list[list_count].duration,
					last_phone,
					next_phone
				);
			}
			else
			{
				for (j = 0; j < length; j++)
				{
					frame_ty	frame;

					frame.f0 = f0[0];
					
					frame.f1 = f1[0];
					frame.f2 = f2[0];
					frame.f3 = f3[0];
					frame.f4 = f4[0];
					frame.f5 = f5[0];
					frame.f6 = f6[0];
					
					frame.bw1 = bw1[0];
					frame.bw2 = bw2[0];
					frame.bw3 = bw3[0];
					frame.bw4 = bw4[0];
					frame.bw5 = bw5[0];
					frame.bw6 = bw6[0];
					
					
					frame.fnz = fnz;
					frame.fnp = fnp;
					frame.av = av[0];
					frame.anp = 0;
					frame.asp = asp;
					frame.af = af;
					frame.a1 = a1;
					frame.a2 = a2;
					frame.a3 = a3;
					frame.a4 = a4;
					frame.a5 = a5;
					frame.a6 = a6;
					frame.ab = ab;
					frame_out(&frame);
#if 0
					/*
					 * the following is a hack
					 * to give the F0 some life
					 */
					if (j < length / 3) 
						f0[0] += 10;
					else
						f0[0] -= 10;
#endif
					if (interp)
					{
						f0[0] += s_f0;
						
						f1[0] += s_f1;
						f2[0] += s_f2;
						f3[0] += s_f3;
						f4[0] += s_f4;
						f5[0] += s_f5;
						f6[0] += s_f6;
						
						bw1[0] += s_bw1;
						bw2[0] += s_bw2;
						bw3[0] += s_bw3;
						bw4[0] += s_bw4;
						bw5[0] += s_bw5;
						bw6[0] += s_bw6;
						
						av[0] += s_av;
					}
				}
			}
			i++;
			list_count++;
			new_word = 0;
		}

		/* give a WORD_BREAK_TIME pause in between words */
		
		if (++h < word_count)
		{
			frame_ty	frame;

			frame.f0 = LastTarget.f0;
			
			frame.f1 = LastTarget.f1;
			frame.f2 = LastTarget.f2;
			frame.f3 = LastTarget.f3;
			frame.f4 = LastTarget.f4;
			frame.f5 = LastTarget.f5;
			frame.f6 = LastTarget.f6;
			
			frame.bw1 = LastTarget.bw1;
			frame.bw2 = LastTarget.bw2;
			frame.bw3 = LastTarget.bw3;
			frame.bw4 = LastTarget.bw4;
			frame.bw5 = LastTarget.bw5;
			frame.bw6 = LastTarget.bw6;
			
			
			
			frame.fnz = LastTarget.fnz;
			frame.fnp = LastTarget.fnp;
			frame.av = 0;
			frame.anp = LastTarget.anp;
			frame.asp = 0;
			frame.af = 0;
			frame.a1 = LastTarget.a1;
			frame.a2 = LastTarget.a2;
			frame.a3 = LastTarget.a3;
			frame.a4 = LastTarget.a4;
			frame.a5 = LastTarget.a5;
			frame.a6 = LastTarget.a6;
			frame.ab = LastTarget.ab;
			for (k = 0; k < WORD_BREAK_TIME/10; k++)
				frame_out(&frame);
		}
	}
	

	done:
	mem_free((char *)ph_list);
	frame_out_collect(out_p, outlen_p);
	
}
