Chris Mullen 2013-2014
swapblock

To Run (in octave) type "default" to generate the random frames, it will then pass these frames into the recursive function "correlate" 
which will create increasingly accurate approximations of the redundant block's location. the redundancy is then written to disk.

warning: due to the large amount of computation required to carry this amount of cross-correlation out, it will take a long time.
This is intended for production quality holographic videos where time is less of a concern, as in everyday use ( see findblock_1). The detail of this 
method is superior to findblock_1 however due to no restrictions on macroblock size.