#include <stdio.h>

#include "features.h"
#include "rules.h"
#include "vowel.h"
#include "var.h"


void gen_vowel(int phone, int segment_dur, int prev_phone, int next_phone)	
{
	int		j;
	unsigned long	features;
	unsigned long	next_feat=-1;
	unsigned long	prev_feat=-1;
	int		offset;
	int		interp=0;
	double		prcnt;
	
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
	double		n_av	= 0;
	
	double		n_f1	= 0;
	double		n_f2	= 0;
	double		n_f3	= 0;
	double		n_f4	= 0;
	double		n_f5	= 0;
	double		n_f6	= 0;
	
	double		n_bw1	= 0;
	double		n_bw2	= 0;
	double		n_bw3	= 0;
	double		n_bw4	= 0;
	double		n_bw5	= 0;
	double		n_bw6	= 0;
	
	int		time_const;
	int		time_count;

	printf("gen_vowel(phone = %s, segment_dur = %d, prev_phone = %s, next_phone = %s)\n", 
	phonemes_name(phone), 
	segment_dur, 
	phonemes_name(prev_phone), //phonemes_name in features.c
	phonemes_name(next_phone));
	
	
	features = Features[phone];

	if (prev_phone != -1)
		prev_feat = Features[prev_phone];
	if (next_phone != -1) 
		next_feat = Features[next_phone];

	if (prev_feat != -1)
	{
		if (prev_feat & VOWEL || prev_feat & SONOR)
		{
			if (prev_feat & FRICA)
				prcnt = .30;
			else 
				prcnt = .95;
				
			f1[0] = f1[0]-(f1[0] - LastTarget.f1) * prcnt; //LastTarget in var.h
			f2[0] = f2[0]-(f2[0] - LastTarget.f2) * prcnt;
			f3[0] = f3[0]-(f3[0] - LastTarget.f3) * prcnt;
			f4[0] = f4[0]-(f4[0] - LastTarget.f4) * prcnt; //LastTarget in var.h
			f5[0] = f5[0]-(f5[0] - LastTarget.f5) * prcnt;
			f6[0] = f6[0]-(f6[0] - LastTarget.f6) * prcnt;
			
			bw1[0] = bw1[0]- (bw1[0] - LastTarget.bw1) * prcnt;
			bw2[0] = bw2[0]- (bw2[0] - LastTarget.bw2) * prcnt;
			bw3[0] = bw3[0]-(bw3[0] - LastTarget.bw3) * prcnt;
			bw4[0] = bw4[0]- (bw4[0] - LastTarget.bw4) * prcnt;
			bw5[0] = bw5[0]- (bw5[0] - LastTarget.bw5) * prcnt;
			bw6[0] = bw6[0]-(bw6[0] - LastTarget.bw6) * prcnt;
			
			
			//f1[0] -= (f1[0] - LastTarget.f1) * prcnt; //LastTarget in var.h
			//f2[0] -= (f2[0] - LastTarget.f2) * prcnt;
			//f3[0] -= (f3[0] - LastTarget.f3) * prcnt;
			//bw1[0] -= (bw1[0] - LastTarget.bw1) * prcnt;
			//bw2[0] -= (bw2[0] - LastTarget.bw2) * prcnt;
			//bw3[0] -= (bw3[0] - LastTarget.bw3) * prcnt;
		}
	}
	if (next_feat != -1)
	{
		if (next_feat & NASAL)
		{
			translate_phone(next_phone,&offset); //get offset
			
			n_av = Nasals[offset].av; //Nasals is a frame_ty
						
			n_f1 = Nasals[offset].f1;
			n_f2 = Nasals[offset].f2;
			n_f3 = Nasals[offset].f3;
			n_f4 = Nasals[offset].f4;
			n_f5 = Nasals[offset].f5;
			n_f6 = Nasals[offset].f6;
			
			
			n_bw1 = Nasals[offset].bw1;
			n_bw2 = Nasals[offset].bw2;
			n_bw3 = Nasals[offset].bw3;
			n_bw4 = Nasals[offset].bw4;
			n_bw5 = Nasals[offset].bw5;
			n_bw6 = Nasals[offset].bw6;
			
		}
	}

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

	time_const = segment_dur;
	time_count = 0;
	for (j=0;j < segment_dur;j+=10)
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

		if (j < (segment_dur/3)) 
			f0[0] += 40;
		else
		{
			if (f0_change != -1000)
				f0[0] -= 25;
			else 
				f0[0] -= 10;
		}

		f0_temp = f0[0];

		if (next_feat != -1)
		{
			if ((next_feat & NASAL) && (j >= segment_dur-35 && j < segment_dur-25))
			{
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

				f1[1] = n_f1;
				f2[1] = n_f2;
				f3[1] = n_f3;
				f4[1] = n_f4;
				f5[1] = n_f5;
				f6[1] = n_f6;
				
				bw1[1] = n_bw1;
				bw2[1] = n_bw2;
				bw3[1] = n_bw3;
				bw4[1] = n_bw4;
				bw5[1] = n_bw5;
				bw6[1] = n_bw6;
				
				av[1] = n_av;
				
				time_const = 10;
				time_count = 0;
				interp = 1;
			}
		}

		if ((features & DIPTH) || interp)
		{
			f0_temp = gen_curve(f0[0],f0[1],time_const/4,time_count);
			
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
		time_count += 10;
		//printf("vowel frame data\n");
		print_frame_data(frame); //print frame data
		//printf("vowel var data\n");
		//pars_ty par =convert_frame_to_par(frame);		
		//print_par_data2(par);
		//klatt_frame_t kframe= convert_frame_to_klatt_frame(frame);
        //print_kframe_data(kframe);
		
		
		frame_out(&frame);
		LastTarget = frame;
	}//for
	
}
