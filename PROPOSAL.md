# Project Proposal
I would like to build a sound synthesis application that generates music that sounds akin to a clarinet (the instrument I play). Users could toggle bars to change the speed, volume, or pitch of the instrument. I have always been interested in music -- as an instrumentalist and a listener -- and I hope this project can give me greater insight into sound synthsis on computers -- its promises, drawbacks, and current capabilities. I do not expect to produce realistic instrumental sound as a result of this project, but I still believe that it would be incredibly interesting to generate musical sounds. 

In order to generate realistic music, I will need to use a synthesis technique. Common synthesis techniques include wavetable synthesis, physical modeling synthesis, and frequency modulation synthesis. Wavetable synthesis functions by reproducing waves periodically. Physical modelling synthesis is more sophisticated; it uses mathematical modeling in order to generate wave forms that are similar to those produces naturally by physical instruments, outputting those. FM synthesis essentially involves changing the timbre of a sound by, as the name suggests, modulating the frequency of the wave. Physical modelling synthesis will produce the most realistic-sounding results, but it will also likely be the most difficult to sucessfully accomplish. Thus, at the moment, I am not entirely sure as to which sound generation method my application will employ.

The ultimate goal of the project is to generate a project that can accomplish three tasks. 
1) Allow the user, either through the keyboard or through buttons on the screen, to play a clarinet synthesizer.
2) Build functions that allow the application to output scales and tunes with variable tempos.
3) Build functions to determine if the user is playing a scale or a tune correctly.

There is a number c++ libraries that I would use in order to generate music: 
Tonic provides progrrammers with functions to generate audio frequency waves. The waves are sign functions, and I am this able to control frequency and amplitude. Tonic: https://github.com/TonicAudio/Tonic

