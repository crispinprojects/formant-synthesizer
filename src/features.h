/* 
 * Copyright (C) 
 * (C) 2022 Alan Crispin
 * (C) 1993 Peter Miller.
 * A re-implementation of formant generation code. 
 * The original code was developed by the late Peter Miller 
 * (Recite project). This code uses six formants rather than the original 
 * three and a number of updates, changes and fixes have been made. 
 * The code can be compiled with gcc version 11.2.1 20220127.
 * 
 * Peter Millers Wiki page with links to his software projects is
 * https://en.wikipedia.org/wiki/Peter_Miller_(software_engineer)
 * 
 * The original Copyright states 
 * 
 *  All rights reserved.
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
 */

#ifndef FEATURES_H
#define FEATURES_H

//#include <stdio.h>
//#include <math.h>

#include "frame.h"



#define VOWEL_TYPE 0
#define SONORANT_TYPE 1
#define NASAL_TYPE 2
#define FRICATIVE_TYPE 3
#define PLOSIVE_TYPE 4
#define AFFRICATE_TYPE 5
#define PSUEDO_VOWEL_TYPE 6

#define VOWELS_START 0
#define AA 0
#define AE 1
#define AH 2
#define AO 3
#define AW 4
#define AX 5
#define AXR 6
#define AY 7
#define EH 8
#define ER 9
#define EXR 10
#define EY 11
#define IH 12
#define IX 13
#define IXR 14
#define IY 15
#define OW 16
#define OXR 17
#define OY 18
#define UH 19
#define UW 20
#define UXR 21
#define YU  22
#define VOWELS_END 22

#define SONORANTS_START 23
#define EL 23
#define HH 24
#define HX 25
#define LL 26
#define LX 27
#define RR 28
#define RX 29
#define WW 30
#define WH 31
#define YY 32
#define SONORANTS_END 32
 
#define NASALS_START 33
#define EM 33
#define EN 34
#define MM 35
#define NN 36
#define NG 37
#define NASALS_END 37

#define FRICATIVES_START 38
#define DH 38
#define FF 39
#define SS 40
#define SH 41
#define TH 42
#define VV 43
#define ZZ 44
#define ZH 45
#define FRICATIVES_END 45

#define PLOSIVES_START 46
#define BB 46
#define DD 47
#define DX 48
#define GG 49
#define GP 50
#define KK 51
#define KP 52
#define PP 53
#define TT 54
#define TQ 55
#define PLOSIVES_END 55

#define AFFRICATES_START 56
#define CH 56
#define JJ 57
#define AFFRICATES_END 56

#define PSUEDO_VOWELS_START 58
#define AXP 58
#define PSUEDO_VOWELS_END 58

#define ALL_END 58

#define WORD_BREAK (ALL_END + 1)

#define VOWEL	((unsigned long)1 << 0)
#define SONOR	((unsigned long)1 << 1)
#define NASAL	((unsigned long)1 << 2)
#define FRICA	((unsigned long)1 << 3)
#define PLOSI	((unsigned long)1 << 4)
#define AFFRI	((unsigned long)1 << 5)
#define PSUED	((unsigned long)1 << 6)
#define ALVEO	((unsigned long)1 << 7)
#define ASPSE	((unsigned long)1 << 8)
#define DENTA	((unsigned long)1 << 9)
#define DIPTH	((unsigned long)1 << 10)
#define F2BAC	((unsigned long)1 << 11)
#define FRONT	((unsigned long)1 << 12)
#define GLOTT	((unsigned long)1 << 13)
#define HIGH	((unsigned long)1 << 14)
#define LABIA	((unsigned long)1 << 15)
#define LATER	((unsigned long)1 << 16)
#define LAX	((unsigned long)1 << 17)
#define LIQGL	((unsigned long)1 << 18)
#define LOW	((unsigned long)1 << 19)
#define PALAT	((unsigned long)1 << 20)
#define PALVE	((unsigned long)1 << 21)
#define RETRO	((unsigned long)1 << 22)
#define RGLID	((unsigned long)1 << 23)
#define ROUND	((unsigned long)1 << 24)
#define SCHWA	((unsigned long)1 << 25)
#define STOP	((unsigned long)1 << 26)
#define YGLID	((unsigned long)1 << 27)
#define SYLLA	((unsigned long)1 << 28)
#define VELAR	((unsigned long)1 << 29)
#define VOICE	((unsigned long)1 << 30)
#define WGLID	((unsigned long)1 << 31)

#define VOWEL_AV 48.0



extern int InhDur[ALL_END + 1];
extern int MinDur[ALL_END + 1];
extern unsigned long Features[ALL_END + 1];
extern frame_ty Vowels[][2];
extern frame_ty Sonorants[];
extern frame_ty Nasals[];
extern frame_ty Fricatives[];
extern frame_ty Fricatives[];
extern frame_ty Plosives[];
extern frame_ty Affricates[];
extern frame_ty Psuedo_vowels[];


#define WORD_BREAK_TIME 100 /* ms */

char *phonemes_type_name(int n);
char *phonemes_name(int n);

#endif /* FEATURES_H */
