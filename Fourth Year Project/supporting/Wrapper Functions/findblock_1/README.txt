Chris Mullen 2013-2014
swapblock

To Run (in octave) type "default" to generate the random frames, it will then call "divide" which will split the 
second frame into macroblocks, each of these macroblocks will then be passed into a normalized-cross-correlation
function to test their similarity with the first frame, if any exists, it is stored in a separate location, 
usually will be 4 unless the block lines up perfectly with the macroblock divide lines.
