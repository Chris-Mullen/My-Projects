%%Chris Mullen 10387763

%% This function shows the decompression stage of the wrapper, it extracts an arbitrary number of frames from
%% a lossless video, and stores them in a folder called decompressed. These frames are then to be reassembled
%% using the swapblock function again, using the reference points created in the findblock stage; this will
%% reassemble the original frames without any data loss.  

function decompress
	system("rm -rf decompressed; mkdir decompressed");
	system("ffmpeg -i compressed.mp4 decompressed/frame%d.png");
	end
