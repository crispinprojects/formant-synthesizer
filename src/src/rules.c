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
 * MANIFEST: functions to translate phonemes to frames
 */

#include <math.h>

#include "features.h"
#include "rules.h"
//#include "trace.h"


void segdur (segment_ty *seg_list, long count)
{
	unsigned long	type;
	int		num_syllables=1;
	int		phone;
	int		phone_count;
	int		inhdur;
	int		mindur;
	unsigned long	next_feature;
	unsigned long	prev_feature;
	int		off;

	printf("segdur(seg_list = %08lX, = %08lX, count = %ld)\n\n",
		(long)seg_list, count);
	off = 0;
	for (phone_count = 0; phone_count < count; phone_count++)
		seg_list[phone_count].duration =
			100 + 25 * (seg_list[phone_count].duration - 1);

	num_syllables = 1;
	for (phone_count = 0; phone_count < count; phone_count++)
	{
		phone = seg_list[phone_count].phone;
#ifdef SYLLABLE_MARKER
		if (phone == SYLLABLE_MARKER)
		{
			if (phone_count > 0)
				seg_list[phone_count - 1].duration += 20;
			syllable++;
			continue;
		}
#endif
		if (phone == WORD_BREAK)
		{
			continue;
		}
		type = Features[phone];
		if
		(
			(type & SYLLA)
		&&
			seg_list[phone_count + 1].phone != WORD_BREAK
		)
		{
			/* rule 4 */
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 85) / 100;
		}
		if ((type & SYLLA) && num_syllables > 1)
		{
			/* rule 5 */
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 80) / 100;
		}
		if ((!type & VOWEL) && phone_count != 0)
		{
			/* rule 6 */
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 85) / 100;
		}
		if (type & VOWEL)
		{
			/* rule 9 */
			if (seg_list[phone_count + 1].phone != WORD_BREAK)
				off = phone_count + 1;
			else
				off = phone_count + 2;
			if
			(
				(Features[seg_list[off].phone] & FRICA)
			&&
				(Features[seg_list[off].phone] & VOICE)
			)
			{
				seg_list[phone_count].duration =
					(seg_list[phone_count].phone * 16) / 10;
			}
			if
			(
				(Features[seg_list[off].phone] & PLOSI)
			&&
				(Features[seg_list[off].phone] & VOICE)
			)
			{
				seg_list[phone_count].duration =
					(seg_list[phone_count].duration * 12) / 10;
			}
			if (Features[seg_list[off].phone] & NASAL)
			{
				seg_list[phone_count].duration =
					(seg_list[phone_count].duration * 85) / 100;
			}
			if (Features[seg_list[off].phone] & PLOSI)
			{
				seg_list[phone_count].duration =
					(seg_list[phone_count].duration * 70) / 100;
			}
		}

		/* rule 10 */
		if (seg_list[phone_count+1].phone != WORD_BREAK)
			off = phone_count + 1;
		else
			off = phone_count + 2;
		next_feature = Features[seg_list[off].phone];
		prev_feature = Features[seg_list[phone_count - 1].phone];
		if ((type & VOWEL) && (next_feature & VOWEL))
		{
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 120) / 100;
		}
		if ((type & VOWEL) && (prev_feature & VOWEL))
		{
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 70) / 100;
		}
		if
		(
			(!type & VOWEL)
		&&
			(!next_feature & VOWEL)
		&&
			(!prev_feature & VOWEL)
		)
		{
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 50) / 100;
		}
		else if ((!type & VOWEL) && (!prev_feature & VOWEL))
		{
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 70) / 100;
		}
		else if ((!type & VOWEL) && (!next_feature & VOWEL))
		{
			seg_list[phone_count].duration =
				(seg_list[phone_count].duration * 70) / 100;
		}
	}

	for (phone_count = 0; phone_count < count; phone_count++)
	{
		phone = seg_list[phone_count].phone;
		if (phone == WORD_BREAK)
		{
			seg_list[phone_count].duration = 0;
			continue;
		}
		mindur = MinDur[phone];
		inhdur = InhDur[phone];
		if (seg_list[phone_count].duration > 0)
			seg_list[phone_count].duration =
				((inhdur - mindur) * seg_list[phone_count].duration) / 100 + mindur;
		else 
			seg_list[phone_count].duration = 0;
		printf
		(
			"Phone %4ld %s len:%4ld\n",
			phone_count,
			phonemes_name(seg_list[phone_count].phone),
			seg_list[phone_count].duration
		 );
	}
	
}


int gen_curve (double Ai, double Af, int time_const, int t)
{
	double	temp1;

	temp1 = exp(-1 * (double)t / (double)time_const);
	temp1 *= (Ai - Af) * (1.0 + ((double)t / (double)time_const));
		
	return (temp1 + Af);
}


int translate_phone (int ph, int *offset)
{
	if (ph <= VOWELS_END)
	{
		*offset = ph;
		return VOWEL_TYPE;
	}
	if (ph <= SONORANTS_END)
	{
		*offset = ph - SONORANTS_START;
		return SONORANT_TYPE;
	}
	if (ph <= NASALS_END)
	{
		*offset = ph - NASALS_START;
		return NASAL_TYPE;
	}
	//old code
	//if (ph <= FRICATIVES_END)
	//{
		//*offset = ph - PLOSIVES_START;
		//return PLOSIVE_TYPE;
	//}
	
	//----------new code----------
	if (ph <= PLOSIVES_END)
	{
		*offset = ph - PLOSIVES_START;
		return PLOSIVE_TYPE;
	}
	
	if (ph <= FRICATIVES_END)
	{
		*offset = ph - FRICATIVES_START;
		return FRICATIVE_TYPE;
	}
	//------------------------
	
	if (ph <= AFFRICATES_END)
	{
		*offset = ph - AFFRICATES_START;
		return AFFRICATE_TYPE;
	}
	if (ph <= PSUEDO_VOWELS_END)
	{
		*offset = ph - PSUEDO_VOWELS_START;
		return PSUEDO_VOWEL_TYPE;
	}
	*offset = -1;
	return -1;
}
