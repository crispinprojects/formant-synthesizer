#include <stdio.h>
#include "features.h"
#include "plosives.h"
#include "rules.h"
#include "var.h"


void gen_plosive(int phone, int segment_dur, int prev_phone, int next_phone)
{
	int		j;
	unsigned long	features;
	unsigned long	next_feat;
	unsigned long	prev_feat;
	int		time_count;
	int		time_const;
	int		off; //offset
	double		f0_temp;
	
	double		f1_temp;
	double		f2_temp;
	double		f3_temp;
	double		f4_temp;
	double		f5_temp;
	double		f6_temp;
	
	double		bw1_temp;
	double		bw2_temp;
	double		bw3_temp;
	double		bw4_temp;
	double		bw5_temp;
	double		bw6_temp;
	
	double		av_temp;

	printf("gen_plosive(phone = %s, segment_dur = %d, prev_phone = %s, next_phone = %s)\n", phonemes_name(phone), segment_dur, phonemes_name(prev_phone), phonemes_name(next_phone));
	features = Features[phone];
	prev_feat = prev_phone >= 0 ? Features[prev_phone] : -1;
	next_feat = next_phone >= 0 ? Features[next_phone] : -1;
	if ((features & VOICE) && (!next_feat & VOWEL))
		av[0] -= 20;

	if (phone == GG || phone == GP)
		av[0] -= 10;

	if (next_feat != -1)
	{
		if (next_feat & VOWEL)
		{
			translate_phone(next_phone, &off);
			
			f1[1] = Vowels[off][0].f1;
			f2[1] = Vowels[off][0].f2;
			f3[1] = Vowels[off][0].f3;
			f4[1] = Vowels[off][0].f4;
			f5[1] = Vowels[off][0].f5;
			f6[1] = Vowels[off][0].f6;
			
			bw1[1] = Vowels[off][0].bw1;
			bw2[1] = Vowels[off][0].bw2;
			bw3[1] = Vowels[off][0].bw3;
			bw4[1] = Vowels[off][0].bw4;
			bw5[1] = Vowels[off][0].bw5;
			bw6[1] = Vowels[off][0].bw6;
			
			
		}
		else if (next_feat & SONOR)
		{
			translate_phone(next_phone, &off);
			
			f1[1] = Sonorants[off].f1;
			f2[1] = Sonorants[off].f2;
			f3[1] = Sonorants[off].f3;
			f4[1] = Sonorants[off].f4;
			f5[1] = Sonorants[off].f5;
			f6[1] = Sonorants[off].f6;
			
			bw1[1] = Sonorants[off].bw1;
			bw2[1] = Sonorants[off].bw2;
			bw3[1] = Sonorants[off].bw3;
			bw4[1] = Sonorants[off].bw4;
			bw5[1] = Sonorants[off].bw5;
			bw6[1] = Sonorants[off].bw6;
		}
	}
	if (prev_feat != -1)
	{
		/* voice onset time = 4 frames = 40 ms*/
		if (prev_feat & VOICE)
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
			frame.anp = 0;
			frame.asp = 0;
			frame.af = 0;
			frame.a1 = LastTarget.a1;
			frame.a2 = LastTarget.a2;
			frame.a3 = LastTarget.a3;
			frame.a4 = LastTarget.a4;
			frame.a5 = LastTarget.a5;
			frame.a6 = LastTarget.a6;
			frame.ab = LastTarget.ab;
			for (j = 0; j < 4; j++)
				frame_out(&frame);
		}
	}

	if (phone == BB || phone == DD)
		time_const = segment_dur * 2;
	else
		time_const = segment_dur;

	time_count = 0;
	f0_temp = f0[0]; 
	
	f1_temp = f1[0]; 
	f2_temp = f2[0]; 
	f3_temp = f3[0]; 
	f4_temp = f4[0]; 
	f5_temp = f5[0]; 
	f6_temp = f6[0]; 
	
	bw1_temp = bw1[0];
	bw2_temp = bw2[0];
	bw3_temp = bw3[0];
	bw4_temp = bw4[0];
	bw5_temp = bw5[0];
	bw6_temp = bw6[0];
	
	
	av_temp = av[0];

	for (j = 0; j < segment_dur; j += 10)
	{
		frame_ty	frame;

		frame.f0 = f0_temp; 
		
		frame.f1 = f1_temp; 
		frame.f2 = f2_temp; 
		frame.f3 = f3_temp; 
		frame.f4 = f4_temp; 
		frame.f5 = f5_temp; 
		frame.f6 = f6_temp; 
		
		frame.bw1 = bw1_temp;
		frame.bw2 = bw2_temp;
		frame.bw3 = bw3_temp;
		frame.bw4 = bw4_temp;
		frame.bw5 = bw5_temp;
		frame.bw6 = bw6_temp;
		
		
		frame.fnz = fnz;
		frame.fnp = fnp;
		frame.av = av_temp;
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

		if (next_feat != -1)
			if (next_feat & (VOWEL | SONOR))
			{
				if (phone == GP || phone == GG)
					av_temp -= 3;
				if (phone == BB || phone == DD) 
					av_temp -= 5;
				
				f0_temp = gen_curve(f0[0], f0[1], time_const/4, time_count); //gen_curve in rules.c
				
				f1_temp = gen_curve(f1[0], f1[1], time_const/4, time_count); 
				f2_temp = gen_curve(f2[0], f2[1], time_const/4, time_count); 
				f3_temp = gen_curve(f3[0], f3[1], time_const/4, time_count); 
				f4_temp = gen_curve(f4[0], f4[1], time_const/4, time_count); 
				f5_temp = gen_curve(f5[0], f5[1], time_const/4, time_count); 
				f6_temp = gen_curve(f6[0], f6[1], time_const/4, time_count); 
				
				
				bw1_temp = gen_curve(bw1[0], bw1[1], time_const/4, time_count); 
				bw2_temp = gen_curve(bw2[0], bw2[1], time_const/4, time_count); 
				bw3_temp = gen_curve(bw3[0], bw3[1], time_const/4, time_count);
				bw4_temp = gen_curve(bw4[0], bw4[1], time_const/4, time_count); 
				bw5_temp = gen_curve(bw5[0], bw5[1], time_const/4, time_count); 
				bw6_temp = gen_curve(bw6[0], bw6[1], time_const/4, time_count);
				
				
				
				time_count += 10;
			}

		if (phone == PP)
		{
			if (j == 20)
				frame.af = 60;
			else if (j > 30 && j < 60)
				frame.asp = 60;
		}
		else if (phone == TT)
		{
			if (j == 10)
				frame.af = 55;
			if (j >= 10)
				frame.asp = 45;
		}
		else if (phone == TQ)
		{
			if (j == 20)
				frame.af = 51;
			if (j >= 20)
				frame.asp = 51;
		}
		else if (phone == KK)
		{
			if (j == 0)
				frame.af = 45;
		}
		else if (phone == KP)
		{
			/* voice onset for /Kh/ = 60ms */
			if (j == 0)
				frame.af = 55;
			else
				frame.asp = 50;
		}
		else if (phone == GG)
		{
			/* voice onset = 10ms */
			if (j >= (segment_dur - 10))
				frame.av = 0;
		}	 
		else if (phone == GP)
		{
			/* voice onset = 10ms */
			if (j >= (segment_dur -	10))
			{
				frame.av = 0;
				frame.asp = 55;
			}
		}	 
		else if (phone == BB)
		{
			if (j < 10 || j > 40)
				frame.av = 0;
			if (j >= 20)
				frame.asp = 40;
		}
		else if (phone == DD)
		{
			if (j < 10)
			{
				frame.av = 0;
			}
		}
		else if (phone == JJ)
		{
			if (j == 0 || j == 10)
			{
				frame.asp = 60;
			}
			if (j <= 40 && j > 0)
			{
				frame.av = 60;
			}
		}		
		else if (phone == CH)
		{
			/* voice onset for /Kh/ = 60ms */
			if (j == 0)
				frame.af = 55;
			else
				frame.asp = 50;
		}
		print_frame_data(frame); //print frame data
		//pars_ty par =convert_frame_to_par(frame);		
		//print_par_data2(par);
		//klatt_frame_t kframe= convert_frame_to_klatt_frame(frame);
       //print_kframe_data(kframe);
		
		
		frame_out(&frame);
		LastTarget = frame;
	}
	//trace((/*{*/"}\n"));
}
