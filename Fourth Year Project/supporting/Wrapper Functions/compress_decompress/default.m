%% This function creates some random frames to test the compression stage of the wrapper, 
%% it takes in an arbitrary set of frames, (which would be created
%% in the swapblock stage earlier) and compresses them to lossless video, making use of ffmpeg's 
%% standard inter-frame coding algorithm without motion estimation.

%%Chris Mullen 10387763
function default
	background=zeros(100,100);
	block=rand(16,16);
	mkrandframes(background,block);
	compress;
	decompress;
	end

%%Chris Mullen 10387763
function mkrandframes(background,block)
	system("rm -rf frames; mkdir frames");
	backsize=rows(background);
	blocksize=rows(block);

	x1=randi(backsize-blocksize);%%random x coordinate
	y1=randi(backsize-blocksize);%%random y coordinate

	x2=x1;
	y2=y1;

	frame1=background;
	frame2=background;

	frame1(x1:x1+blocksize-1,y1:y1+blocksize-1)=block;
	frame2(x2:x2+blocksize-1,y2:y2+blocksize-1)=block;

	imwrite(frame1,"frames/frame1.png");
	imwrite(frame2,"frames/frame2.png");
	end
