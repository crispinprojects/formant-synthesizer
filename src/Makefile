
LIBS= -lm
# formant synthesizer development makefile

speak: main.c phonemes.o features.o frame.o fricatives.o mem.o plosives.o rules.o sonorants.o var.o vowel.o parwave.o 
	gcc main.c phonemes.o features.o frame.o fricatives.o mem.o plosives.o rules.o sonorants.o var.o vowel.o parwave.o  $(LIBS) -o speak

phonemes.o: phonemes.c phonemes.h
	gcc -c phonemes.c -o phonemes.o

features.o: features.c features.h
	gcc -c features.c -o features.o

frame.o: frame.c frame.h
	gcc -c frame.c -o frame.o

fricatives.o: fricatives.c fricatives.h
	gcc -c fricatives.c -o fricatives.o

mem.o: mem.c mem.h
	gcc -c mem.c -o mem.o
	
plosives.o: plosives.c plosives.h
	gcc -c plosives.c -o plosives.o

rules.o: rules.c rules.h
	gcc -c rules.c -o rules.o

sonorants.o: sonorants.c sonorants.h
	gcc -c sonorants.c -o sonorants.o

var.o: var.c var.h
	gcc -c var.c -o var.o
	
vowel.o: vowel.c vowel.h
	gcc -c vowel.c -o vowel.o

parwave.o: parwave.c parwave.h
	gcc -c parwave.c -o parwave.o	


# the clean target removes any object and executable files
# created by this makefile
clean:
	rm -f *.o speak


	
