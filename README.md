# Formant Speech Synthesizer

The code generates formant frames from a set of phonetic transcription codes known as [ARPABET](https://en.wikipedia.org/wiki/ARPABET) for a Klatt synthesizer. A Klatt Synthesizer is a software synthesizer for generating speech designed by Dennis Klatt in [1980](https://www.fon.hum.uva.nl/david/ma_ssp/2010/Klatt-1980-JAS000971.pdf). With the help of [Peter Miller's](https://en.wikipedia.org/wiki/Peter_Miller_(software_engineer) Recite project I was able generate frames of Klatt parameters with each frame consisting of forty parameters describing formant frequencies, amplitudes, bandwidths, voicing, frication etc. This required code to model vowels, sonorants, fricatives and plosives. The generated frames were used to produce speech using an implementation of the Klatt Cascade-Parallel Formant Speech Synthesizer developed by Reece H. Dunn and found [here on github](https://github.com/rhdunn/klatt).


## Compile

Use the MAKEFILE to compile.

```
make
./speak
```
You should hear the formant speech synthesizer saying "Hello world I am a speech synthesizer"

## Summary

Unfortunately, I could not get satisfactory results in terms of audible speech with this approach to speech synthesis. This was dissapointing.

I have also developed a diphone speech synthesizer which is used in my GTK4 [Talking Calendar](https://github.com/crispinprojects/talkingcalendar) project.

