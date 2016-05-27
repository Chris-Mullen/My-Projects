Chris Mullen 2013-2014
Experiment 1C

To Run (in octave) type "holo" to generate the frames.
"holread" will read in the complex valued hologram file and remove it's amplitude producing a phase-only image
"mpg" is called from this function, which compresses the frame to video.
playback is enabled by default

default parameters:
holo(fname="chip4",mkvid=true,play=false,frameout=true)

	%%fname=Name of hologram file (without ".hol" extension)
	%%mkvid=true means compress frames to video
	%%play=true means play thecompressed video
	%%frameout=true means decompress video file to it's componant frames