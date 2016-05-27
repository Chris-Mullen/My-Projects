%%Chris Mullen 2013-2014
%%Experiment 1A

%%This Compresses the frames created in gen.m to video and has can also play them if specified

function mpg(play=true)
	tmpdir;
	%-me_method zero 				%zero motion estimation
	%-me_method epzs 				%default motion estimation
	%-me_method full				%full motion estimation (esa ())
	%-me_method tesa				%improvement on full motion estimation
	%-g <int>						%frame distance between i-frames (0 makes all frames i-frames)
	%-bf <int>						%number of b-frames between each anchor frame(p/i)
	system("ffmpeg -f image2 -i normal/frame%d.png -g 0 -loglevel verbose mpg-out/test1a.mp4");
	system("ffmpeg -f image2 -i flipped/frame%d.png -g 0 -loglevel verbose mpg-out/test1b.mp4");
	system("ffmpeg -f image2 -i normal/frame%d.png -me_method tesa -loglevel verbose mpg-out/test2a.mp4");
	system("ffmpeg -f image2 -i flipped/frame%d.png -me_method tesa -loglevel verbose mpg-out/test2b.mp4");

	%-q:v <int> 					%video quality (1-31) 1=best quality
	system("ffmpeg -i mpg-out/test1a.mp4 -q:v 1 -loglevel verbose frames-out/test1a/tmp/frame%d.png");
	system("ffmpeg -i mpg-out/test1b.mp4 -q:v 1 -loglevel verbose frames-out/test1b/tmp/frame%d.png");
	system("ffmpeg -i mpg-out/test2a.mp4 -q:v 1 -loglevel verbose frames-out/test2a/tmp/frame%d.png");
	system("ffmpeg -i mpg-out/test2b.mp4 -q:v 1 -loglevel verbose frames-out/test2b/tmp/frame%d.png");
	reprocess;%%reads in all frames in octave and rewrites them (octave compresses more efficiently than ffmpeg by default)

	if(play==true)
		%%Play videos on loop with ffplay
		system("ffplay -i mpg-out/test1a.mp4 -loop 0");
		system("ffplay -i mpg-out/test1b.mp4 -loop 0");
		system("ffplay -i mpg-out/test2a.mp4 -loop 0");
		system("ffplay -i mpg-out/test2b.mp4 -loop 0");
		endif
	dispfilesize;%%Displays video file sizes
	end

function tmpdir
	system("rm -rf mpg-out; mkdir mpg-out;");
	system("rm -rf frames-out;");
	if(exist("normal","dir"))
	else
		mkdir("normal");
		printf("run \"gen\" to generate frames\n");
		end
	if(exist("flipped","dir"))
	else
		mkdir("flipped");
		printf("run \"gen\" to generate frames\n");
		end
	if(exist("frames-out","dir"))
	else
		system("mkdir frames-out");
		system("mkdir frames-out/test1a; mkdir frames-out/test1b; mkdir frames-out/test2a; mkdir frames-out/test2b;");
		system("mkdir frames-out/test1a/tmp; mkdir frames-out/test1b/tmp; mkdir frames-out/test2a/tmp; mkdir frames-out/test2b/tmp;");
		end
	end
function reprocess
	for count = 1:10
		a=imread(sprintf('frames-out/test1a/tmp/frame%d.png',count));
		a=imread(sprintf('frames-out/test1b/tmp/frame%d.png',count));
		b=imread(sprintf('frames-out/test2a/tmp/frame%d.png',count));
		b=imread(sprintf('frames-out/test2b/tmp/frame%d.png',count));
	    imwrite(a,sprintf('frames-out/test1a/frame%d.png',count),8);
	    imwrite(a,sprintf('frames-out/test1b/frame%d.png',count),8);
		imwrite(b,sprintf('frames-out/test2a/frame%d.png',count),8);
		imwrite(b,sprintf('frames-out/test2b/frame%d.png',count),8);
	    endfor
	system("rm -rf frames-out/test1a/tmp");
	system("rm -rf frames-out/test1b/tmp");
	system("rm -rf frames-out/test2a/tmp");
	system("rm -rf frames-out/test2b/tmp");
	end
function dispfilesize
	system("ls mpg-out -la");
	end
