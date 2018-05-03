# CS 126 FinalProject
This application allows its user to generate semi-realistic-sounding clarinet pitches by pressing buttons on their keyboard. They can change the volume and octave of these pitches, as well as play scales, record sequences notes, playback sequences of notes, and compare two recordings. While notes are playing, a diagram of the clarinet will show which keys/holes must be pressed. The user can see a full list of instructions by pressing p and brining up the pause screen. Here is an abridged version:

1) Keys A-J in the second row correspond to major pitches, while Q, W, E, T, Y, and I correspond to accidentials.
2) The volume can be changed with the slider or + - keys.
3) The octave can be toggled with the button or shift key.
4) Use the record, playback, and compare buttons to record, playback, and compare recordings.
5) Press the scale buttons to play scales.

In order to run the application, users must install openFrameworks and Tonic, the library used to generate sine waves. In order to generate the images, the user must ensure that the images for the different clarinet fingerings, which can be found in the bin/data folder of this repository, are downloaded. In order to run the tests, the user must ensure they have the catch.hpp file -- which is located in this repository as well.
