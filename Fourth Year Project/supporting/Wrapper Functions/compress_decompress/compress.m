%%Chris Mullen 10387763

%% This function shows the compression stage of the wrapper, it takes in an arbitrary set of frames, (created
%% with the swapblock function earlier) and compresses them to lossless video, making use of ffmpeg's 
%% standard inter-frame coding algorithm without motion estimation.

function compress
	system("ffmpeg -f image2 -i frames/frame%d.png -c:v libx264 -preset veryslow -crf 0 -me_method tesa -loglevel verbose compressed.mp4");
	system("ffplay -i compressed.mp4");
	end
