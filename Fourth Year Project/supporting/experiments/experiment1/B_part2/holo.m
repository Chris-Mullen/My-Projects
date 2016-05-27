%%Chris Mullen 2013-2014
%%Experiment 1B_part2

%%This File Has The Same Function As noise.m (from experiment 1B_part1) but loads and uses a digital hologram 
%%phase-only image instead of a noise pattern to check scalability

function holo(fname="chip4",mkvid=true,play=false,frameout=true)
	%%fname=Name of hologram file (without ".hol" extension)
	%%mkvid=true means compress frames to video
	%%play=true means play thecompressed video
	%%frameout=true means decompress video file to it's componant frames

    system("rm -rf mpg-out; mkdir mpg-out");
    system("rm -rf frames; mkdir frames");
	system("mkdir frames/tmp");
    openfile(fname);%%open hologram, remove amplitude, save phase as a .png image
	noise=imread("tmp/out.png");
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

%%CM
function mpg
	%% -c:v libx264 -preset veryslow     	            %%best compression
    %% -c:v libx264 -preset ultrafast	                %%worst compression
	%% -crf 0											%%quantizer scale, 0 means lossless
    system("ffmpeg -i frames/tmp/frame%d.png -c:v libx264 -preset veryslow -crf 0 -me_method tesa -loglevel verbose mpg-out/test1.mp4");
    system("ffmpeg -i frames/tmp/frame%d.png -c:v libx264 -preset veryslow -crf 0 -g 0 -loglevel verbose mpg-out/test2.mp4");
	dispfilesize;%%display video file sizes
	end

%%CM
function frames
	system("rm -rf frames-out");
	system("mkdir frames-out; mkdir frames-out/test1; mkdir frames-out/test2");
	system("mkdir frames-out/test1/tmp; mkdir frames-out/test2/tmp");
	system("ffmpeg -i mpg-out/test1.mp4 -crf 0 -loglevel verbose frames-out/test1/tmp/frame%d.png");
	system("ffmpeg -i mpg-out/test2.mp4 -crf 0 -loglevel verbose frames-out/test2/tmp/frame%d.png");
	end

%%CM
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

%%CM
function openfile(filename)
	system("rm -rf tmp");
	system("mkdir tmp");
    disp(filename);printf("\n");
    hol=holread(filename);
    %%hol=exp(i*angle(hol));
    a=angle(hol)+pi;
    a=a./max(max(a));
    qa=round(a*3);
	imwrite(qa,"tmp/out.png");
    end

% Reading a hologram file
% Modified 8/18/00
%% tjn 03 III 2005
%% tjn 20 III 2012, call error if file not exist

function A=holread(name,ext);

if (nargin < 2)
  ext = 'hol';
end

fname = [name,'.',ext];
f1=fopen(fname,'r');
if f1==-1
   error(['The file ''',fname,''' does not exist.'])
   return
end
t=fread(f1,1,'int8');
Ny=fread(f1,1,'uint32'); %- was uint
Nx=fread(f1,1,'uint32'); %- was uint
if t==1
   A=fread(f1,[Ny,Nx],'double');
   s=sprintf('Reading %dx%d real',Nx,Ny);
elseif t==2
   Ar=fread(f1,[Ny,Nx],'double');
   Ai=fread(f1,[Ny,Nx],'double');
   A=Ar+j*Ai;
   s=sprintf('Reading %dx%d complex',Ny,Nx);
else
   error(['Unknown header byte of ',int2str(t),'.']);
end
disp([s,' from ',fname]);
fclose(f1);
end

%%CM
function dispfilesize
	system("ls mpg-out -la");
	end
