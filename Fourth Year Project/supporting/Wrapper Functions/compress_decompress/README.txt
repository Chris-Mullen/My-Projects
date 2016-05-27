Chris Mullen 2013-2014
compress_decompress

To Run (in octave) type "default" to generate the frames, it will then call "compress" to encode,
and then call "decompress" to decode using the recorded reference points. These frames are then used with the swapblock function again to 
reassemble the original frames.

these reference points are taken from one of the findblock functions originally