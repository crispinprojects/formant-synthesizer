# Formant Speech Synthesizer

This is an example of a formant speech syntheiszer which replicates speech using [formants](https://www.youtube.com/watch?v=QS0iAyXWs5I). If you plot amplitude verses frequency of a typical speaker then formants are the resonance points or spectral peaks in the spectral envelop. They are the harmonics that are accentuated more than the other frequencies. Formant is a word derived from the Latin formare, meaning "to shape" in this case the sounds of vocal track.

The code generates formant frames from a set of phonetic transcription codes known as [ARPABET](https://en.wikipedia.org/wiki/ARPABET) for a Klatt synthesizer. A Klatt Synthesizer is a software synthesizer for generating speech designed by Dennis Klatt in [1980](https://www.fon.hum.uva.nl/david/ma_ssp/2010/Klatt-1980-JAS000971.pdf). With the help of [Peter Millers](https://en.wikipedia.org/wiki/Peter_Miller_(software_engineer)) Recite project I was able generate frames of Klatt parameters with each frame consisting of forty parameters describing formant frequencies, amplitudes, bandwidths, voicing, frication etc. This required code to model vowels, sonorants, fricatives and plosives. The generated frames are used to produce speech using an implementation of the Klatt Cascade-Parallel Formant Speech Synthesizer developed by Reece H. Dunn and found [here on github](https://github.com/rhdunn/klatt).

## Compile

Use the MAKEFILE to compile. The target is "fspeak"

```
make fspeak
./fspeak
```

You should hear the formant speech synthesizer saying "Hello world I am a speech synthesizer"

## Summary

Unfortunately, the synthesizer produces robotic speech. Compile the code and listen to it say "Hello world I am a speech synthesizer"

I was hoping to use the formant speech synthesizer in my GTK4 [Talk Calendar](https://github.com/crispinprojects/talkcalendar) project. However I am currently using my own diphone concentation speech synthesizer for this project.
