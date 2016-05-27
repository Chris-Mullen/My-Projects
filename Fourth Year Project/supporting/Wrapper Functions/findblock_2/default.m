%% This function generates frames and passes them into the findblk function to be divided into macroblocks and 
%% cross-correlated to find redundancies

%%Chris Mullen 10387763
function default
	background=zeros(100,100);
	block=rand(16,16);
imwrite(block,"blk.png");
	mkrandframes(background,block);
	frame1=imread("frames/frame1.png");
	frame2=imread("frames/frame2.png");

	imwrite(frame1,"frame1.png");
	imwrite(frame2,"frame2.png");
	findblk(frame1,frame2);
	end

%%Chris Mullen 10387763
function qa=quantize(a,num)
	a=a./max(max(a));
    qa=round(a*num);
	end

%%Chris Mullen 10387763
function savefiles(frame1,frame2,block)
	system("rm -rf backup");
	system("mkdir backup");
	cd backup;
	save frame1.mat frame1;
	save frame2.mat frame2;
	save block.mat block;
	cd ../
	end

%%Chris Mullen 10387763
function mkrandframes(background,block)
	system("rm -rf frames; mkdir frames");
	backsize=rows(background);
	blocksize=rows(block);

	x1=randi(backsize-blocksize);
	y1=randi(backsize-blocksize);

	frame1=background;
	frame2=background;

	frame1(x1:x1+blocksize-1,y1:y1+blocksize-1)=block;

	x2=randi(backsize-blocksize);%%random x coordinate
	y2=randi(backsize-blocksize);%%random y coordinate

	frame2(x2:x2+blocksize-1,y2:y2+blocksize-1)=block;

	imwrite(frame1,"frames/frame1.png");
	imwrite(frame2,"frames/frame2.png");
	end
