/*
 * Copyright (C) 
 * (C) 2022 Alan Crispin
 * (C) 1993 Peter Miller.
 * A re-implementation of formant generation code. 
 * The original code was developed by the late Peter Miller 
 * (Recite project). This is main.c used for development testing.
 * 
*/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h>

#include "phonemes.h"
#include "vowel.h"
#include "frame.h"
#include "mem.h"

int main(int argc, char **argv)
{
	printf("Development files for Formant Speech Synthesizer\n");
		
	char	*data;
	long	datalen;
	
	//HHAHLLOW WWER,LLDD"; //Hello World
	//"AY AEMM AH"; // I am a
	//S P IY1 CH //speech
	//S IH1 N TH AH0 S AY2 Z ER0 //synthesizer
	
	data ="HHAHLLOW WWER,LLDD. AY AEMM AH, SSPPIY,CH SSIH,NNTHAH,SSAY,,ZZER, "; 
	
	datalen =strlen(data);
	
	printf("data = %s\n", data);
	printf("datalen = %i\n", datalen);
	
	
	char	*tmp;
	long	tmplen;
	
	phonemes_to_klatt(data, datalen, &tmp, &tmplen);
	
	data = tmp;
	datalen = tmplen;
	
	char *outfilename;
	outfilename ="sample.par";	
	frame_write_klatt(outfilename,data,datalen);
	
	char *parfilename ="sample.par";
	char *wavfilename ="sample.raw";	
	write_wav(parfilename, wavfilename);
		
	char* aplay_str ="aplay -r 10000 -c 1 -f S16_LE sample.raw"; 
    system(aplay_str);  
	
}	
