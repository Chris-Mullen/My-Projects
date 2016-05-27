Chris Mullen 2013-2014
swapblock

To Run (in octave) type "default" to generate the frames, it will then call "swapblock" to encode, and record reference points,
and then call it again to decode using the recorded reference points.

%% This function creates a frame and calls my swapblock function twice, once to represent encoding, 
%% and once to represent decoding.
%% Three images will be output: the original frame ("Before.png"), The encoded state ("Intermediate.png")
%% And The decoded state ("After.png"). (Before and after should be the same image)

these reference points are taken from one of the findblock functions