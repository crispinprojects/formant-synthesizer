#include <stdio.h>
#include "features.h"
#include "rules.h"
#include "sonorants.h"
#include "var.h"


void gen_sonorant(int phone, int segment_dur, int prev_phone, int next_phone)
{
	int		j;
	unsigned long	features;
	unsigned long	next_feat=-1;
	unsigned long	prev_feat=-1;
	int		off; //offset
	int		interp2=0;
	int		interp=0;
	int		length;
	int		time_count;
	int		time_const;
	
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

	printf("gen_sonorant(phone = %s, segment_dur = %d, prev_phone = %s, next_phone = %s)\n", phonemes_name(phone), segment_dur, phonemes_name(prev_phone), phonemes_name(next_phone));
	length = segment_dur/10;
	
	features = Features[phone];

	if (prev_phone != -1)
		prev_feat = Features[prev_phone];
	if (next_phone != -1) 
		next_feat = Features[next_phone];

	if (next_feat != -1)
	{
		if (next_feat & VOWEL)
		{
			//trace(("mark\n"));
			/* sonorants move to a following voiced segment */
			translate_phone(next_phone,&off);
			av[1] = VOWEL_AV;
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
			
			
			interp = 1;
			interp2 = 1;
		}
		else if (next_feat & NASAL)
		{
			//trace(("mark\n"));
			translate_phone(next_phone,&off);
			av[1] = Nasals[off].av;
			
			f1[1] = Nasals[off].f1;
			f2[1] = Nasals[off].f2;
			f3[1] = Nasals[off].f3;
			f4[1] = Nasals[off].f4;
			f5[1] = Nasals[off].f5;
			f6[1] = Nasals[off].f6;
			
			bw1[1] = Nasals[off].bw1;
			bw2[1] = Nasals[off].bw2;
			bw3[1] = Nasals[off].bw3;
			bw4[1] = Nasals[off].bw4;
			bw5[1] = Nasals[off].bw5;
			bw6[1] = Nasals[off].bw6;
			
			interp = 1;
		}
	}

	//trace(("mark\n"));
	
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

	time_const = segment_dur;		
	time_count = 0;
	for (j = 0; j < segment_dur; j += 10)
	{
		frame_ty	frame;

		//trace(("mark\n"));
		frame.f0 = f0[0]; 
		
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

		if (f0_change != -1000)
			f0[0] += f0_change;
		else 
			f0[0] -= 20;

		if (interp && interp2)
		{
			if (next_feat & NASAL)
			{
				//trace(("mark\n"));
				f1_temp = gen_curve(f1[0],f1[1],10,time_count); 
				f2_temp = gen_curve(f2[0],f2[1],10,time_count); 
				f3_temp = gen_curve(f3[0],f3[1],10,time_count); 
				f4_temp = gen_curve(f4[0],f4[1],10,time_count); 
				f5_temp = gen_curve(f5[0],f5[1],10,time_count); 
				f6_temp = gen_curve(f6[0],f6[1],10,time_count); 
				
				bw1_temp = gen_curve(bw1[0],bw1[1],10,time_count); 
				bw2_temp = gen_curve(bw2[0],bw2[1],10,time_count); 
				bw3_temp = gen_curve(bw3[0],bw3[1],10,time_count);
				bw4_temp = gen_curve(bw4[0],bw4[1],10,time_count); 
				bw5_temp = gen_curve(bw5[0],bw5[1],10,time_count); 
				bw6_temp = gen_curve(bw6[0],bw6[1],10,time_count);
				
				av_temp = gen_curve(av[0],av[1],10,time_count);
			}
			else
			{
				//trace(("mark\n"));
				f1_temp = gen_curve(f1[0],f1[1],time_const/4,time_count); 
				f2_temp = gen_curve(f2[0],f2[1],time_const/4,time_count); 
				f3_temp = gen_curve(f3[0],f3[1],time_const/4,time_count); 
				f4_temp = gen_curve(f4[0],f4[1],time_const/4,time_count); 
				f5_temp = gen_curve(f5[0],f5[1],time_const/4,time_count); 
				f6_temp = gen_curve(f6[0],f6[1],time_const/4,time_count); 
				
				bw1_temp = gen_curve(bw1[0],bw1[1],time_const/4,time_count); 
				bw2_temp = gen_curve(bw2[0],bw2[1],time_const/4,time_count); 
				bw3_temp = gen_curve(bw3[0],bw3[1],time_const/4,time_count);
				bw4_temp = gen_curve(bw4[0],bw4[1],time_const/4,time_count); 
				bw5_temp = gen_curve(bw5[0],bw5[1],time_const/4,time_count); 
				bw6_temp = gen_curve(bw6[0],bw6[1],time_const/4,time_count);
				
				av_temp = gen_curve(av[0],av[1],time_const/4,time_count);
			}
		}

		if ((j > 60) && (features & NASAL))
			interp2 = 1;
		else if ((j > 10) && (!features & NASAL))
			interp2 = 1;

		if (next_feat != -1)
		{
			if ((next_feat & NASAL) && (j == segment_dur-50))
			{
				//trace(("mark\n"));
				f1[0] = f1_temp;
				f2[0] = f2_temp;
				f3[0] = f3_temp;
				f4[0] = f4_temp;
				f5[0] = f5_temp;
				f6[0] = f6_temp;
								
				bw1[0] = bw1_temp;
				bw2[0] = bw2_temp;
				bw3[0] = bw3_temp;
				bw4[0] = bw4_temp;
				bw5[0] = bw5_temp;
				bw6[0] = bw6_temp;
								
				av[0] = av_temp;
				interp2 = 1;
				time_count = -10;
			}
		}

		time_count += 10;
		//printf("Sonorant data\n");
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
