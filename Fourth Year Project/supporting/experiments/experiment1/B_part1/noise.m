%%Chris Mullen 10387763
%%Experiment 1B_part1

%%This experiment is to see if ffmpeg motion estimation has any effect on noise data

%%Chris Mullen 10387763
function noise(mkvid=true,play=true,frameout=false)
	%%mkvid=true means compress frames to video
	%%play=true means play the created video
	%%frameout=true means decompress the video files into their componant frames

    system("rm -rf mpg-out;");
    system("rm -rf frames; mkdir frames");
	system("mkdir frames/tmp");
    noise=rand(250);
    background=zeros(rows(noise)+50,columns(noise)+50);
    frame=background;
    %imwrite(noise,"noise.png");
    %imwrite(background,"background.png");
    frame(25:rows(noise)+24,25:columns(noise)+24)=noise;
    imwrite(frame,"frames/tmp/frame1.png");
    frame=background;
    frame(5:rows(noise)+4,5:columns(noise)+4)=noise;
    imwrite(frame,"frames/tmp/frame2.png");
    frame=background;
    frame(5:rows(noise)+4,25:columns(noise)+24)=noise;
    imwrite(frame,"frames/tmp/frame3.png");
    frame=background;
    frame(5:rows(noise)+4,45:columns(noise)+44)=noise;
    imwrite(frame,"frames/tmp/frame4.png");
    frame=background;
    frame(25:rows(noise)+24,45:columns(noise)+44)=noise;
    imwrite(frame,"frames/tmp/frame5.png");
    frame=background;
    frame(45:rows(noise)+44,45:columns(noise)+44)=noise;
    imwrite(frame,"frames/tmp/frame6.png");
    frame=background;
    frame(45:rows(noise)+44,25:columns(noise)+24)=noise;
    imwrite(frame,"frames/tmp/frame7.png");
    frame=background;
    frame(45:rows(noise)+44,5:columns(noise)+4)=noise;
    imwrite(frame,"frames/tmp/frame8.png");
    frame=background;
    frame(25:rows(noise)+24,5:columns(noise)+4)=noise;
    imwrite(frame,"frames/tmp/frame9.png");
    frame=background;
    frame(5:rows(noise)+4,5:columns(noise)+4)=noise;
    imwrite(frame,"frames/tmp/frame10.png");
	if(mkvid==true)
		system("mkdir mpg-out");
		mpg;%%compress frames into mpg
		if(frameout==true)
			frames;%%decompress frames from mpg
			reprocess;%%reads in all frames in octave and rewrites them (octave compresses more efficiently than ffmpeg by default)
			endif
		if(play==true)
			%%Play videos on loop with ffplay
			system("ffplay -i mpg-out/test1.mp4 -loop 0");
			system("ffplay -i mpg-out/test2.mp4 -loop 0");
			endif
		else
			if(play==true)
				printf("video not present, \"mkvid\" should equal true\n");
				endif
		endif
    end

%%Chris Mullen 10387763
function mpg
	%% -c:v libx264 -preset veryslow     	            %%best compression
    %% -c:v libx264 -preset ultrafast	                %%worst compression
	%% -crf 0											%%quantizer scale, 0 means lossless
    system("ffmpeg -i frames/tmp/frame%d.png -c:v libx264 -preset veryslow -crf 0 -me_method tesa -loglevel verbose mpg-out/test1.mp4");
    system("ffmpeg -i frames/tmp/frame%d.png -c:v libx264 -preset veryslow -crf 0 -g 0 -loglevel verbose mpg-out/test2.mp4");
	dispfilesize;%%display video file sizes
	end

%%Chris Mullen 10387763
function frames
	system("rm -rf frames-out");
	system("mkdir frames-out; mkdir frames-out/test1; mkdir frames-out/test2");
	system("mkdir frames-out/test1/tmp; mkdir frames-out/test2/tmp");
	system("ffmpeg -i mpg-out/test1.mp4 -loglevel verbose frames-out/test1/tmp/frame%d.png");
	system("ffmpeg -i mpg-out/test2.mp4 -loglevel verbose frames-out/test2/tmp/frame%d.png");
	end

%%Chris Mullen 10387763
function reprocess
	for count = 1:10
		a=imread(sprintf('frames-out/test1/tmp/frame%d.png',count));
		b=imread(sprintf('frames-out/test2/tmp/frame%d.png',count));
		c=imread(sprintf('frames/tmp/frame%d.png',count));
	    imwrite(a,sprintf('frames-out/test1/frame%d.png',count),8);
		imwrite(b,sprintf('frames-out/test2/frame%d.png',count),8);
		imwrite(c,sprintf('frames/frame%d.png',count),8);
	    endfor
	system("rm -rf frames-out/test1/tmp");
	system("rm -rf frames-out/test2/tmp");
	system("rm -rf frames/tmp");
	end

%%Chris Mullen 10387763
function dispfilesize
	system("ls mpg-out -la");
	end
