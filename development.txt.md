<b> Progress So Far </b>
My project broadly falls into three phases. I have essentially completed the first, and most work-intensive, phase. 
The first phase involves creating the note generation algorithm, modelling the sine wave synthesis after the physical sounds of the clarinet. This requires a sinewave for the base frequency, as well as six modulators to alter this frequency, each of which has a different magnitude and frequency of its own. This step also required me to determine what the base resonant frequencies are on the clarinet for each major and minor pitch.
Once the note generation method is built, I needed to add methods that allowed users to increase or decrease their volume, as well as change the octave of the notes they were playing.
On the front end, the first phase also involves building the graphic user interface. It involves an animation wherein a clarinet on the screen shows the fingering of the note that is being played. I also needed to structure the audio output in such a way that music only comes out when buttons corresponding to notes are pressed -- and not always or during other commands. Lastly, I needed to create a slider to adjust volume and a button to toggle between the higher and lower octave.

<b> Issues </b>
Up until this point, many of my issues have centered around learning FM-synthesis. I needed to perform research to understand the process of how notes are generated electronically, as well as the frequency percentages that correspond to each step in the note generation project. I also needed to reerse engineer the the number, amplitude, and frequency of the modulators based on the resonant frequency graph of the clarinet -- a process that took hours. 
In addition, I attempted to added ADSR (attack, decay, sustain, release) envelopes to the sound in order to make it sound more realistic, but after multiple hours of experimentation, I was not able to determine the envelope values that would function without unduly distorting the sound. 
Outside of learning FM synthesis, some of the syntactical oddities of tonic have created issues. For example, if I place paranthesis around one of the sinewaves, the function stops outputting sound.
Lastly, it took a substantial amount of time for me to determine why the ofSoundStream.setup() function was not working -- the sample rate used by the speakers on my laptop is 48000, not 44,100 as is the default on most other laptops.

<b> To-Do </b>
1) I need to add more documentation to the methods and instance variables, making it more clear as to how the application functions.
2) I need to build methods that generate basic scales.
3) I need to build methods to generate basic tunes.
4) I need to build a method that takes user playing input and determines if they have made any mistakes.
