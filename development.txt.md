<b> Progress So Far </b>
My project broadly falls into three phases. I have  completed the first and second phases phase. 
The first phase involves creating the note generation algorithm, modelling the sine wave synthesis after the physical sounds of the clarinet. This requires a sinewave for the base frequency, as well as six modulators to alter this frequency, each of which has a different magnitude and frequency of its own. This step also required me to determine what the base resonant frequencies are on the clarinet for each major and minor pitch.
Once the note generation method is built, I needed to add methods that allowed users to increase or decrease their volume, as well as change the octave of the notes they were playing.
On the front end, the first phase included building the graphic user interface. It involves an animation wherein a clarinet on the screen shows the fingering of the note that is being played. I also needed to structure the audio output in such a way that music only comes out when buttons corresponding to notes are pressed -- and not always or during other commands. Lastly, I needed to create a slider to adjust volume and a button to toggle between the higher and lower octave.

The second phase involved creating methods to string multiple notes together, playing scales at a rate specified by the user's beat-per-minute input. During this phase, I ran into a difficult issue: while the playScale method is looping through each note in the scale, the main thread does not call the draw method. Even when I attempted to call the draw method from within the playScale method, the frame did not update. In order to resolve this issue, I needed to create a second thread to output audio. I also needed to use std::clock to align the two threads and switch notes at even intervals.

<b> Issues </b>
During the second phase, needing to build a second thread presented a major issue. I have never used multithreading before, and my first few attempts/iterations were plagued by segfaults. Aside from learing multithreading and ensuring that resources were not attempting to be accessed by both threads, I needed to learn how to output audio outside of the main thread in openFrameworks, and I  needed to refactor all of my audio output methods into a new class. 

During the first phase, many of my issues have centered around learning FM-synthesis. I needed to perform research to understand the process of how notes are generated electronically, as well as the frequency percentages that correspond to each step in the note generation project. I also needed to reerse engineer the the number, amplitude, and frequency of the modulators based on the resonant frequency graph of the clarinet -- a process that took hours. 
In addition, I attempted to added ADSR (attack, decay, sustain, release) envelopes to the sound in order to make it sound more realistic, but after multiple hours of experimentation, I was not able to determine the envelope values that would function without unduly distorting the sound. 
Outside of learning FM synthesis, some of the syntactical oddities of tonic have created issues. For example, if I place paranthesis around one of the sinewaves, the function stops outputting sound.
Lastly, it took a substantial amount of time for me to determine why the ofSoundStream.setup() function was not working -- the sample rate used by the speakers on my laptop is 48000, not 44,100 as is the default on most other laptops.

<b> To-Do </b>
1) I need to add more documentation to the methods and instance variables, making it more clear as to how the application functions.
2) I need to to build a function that will record the user's input and play it back. 
3) I need to build a method that takes user playing input and determines if they have made any mistakes.
4) I need to add a pause screen detailing instructions to the application.
