%% This function takes in two frames, divides one into macroblocks, then cross-correlates each macroblock
%% with the other frame to detect redundancies

%%Chris Mullen 10387763
function findblk(frame1,frame2)
	correlate(frame1,frame2);
	end

%%Chris Mullen 10387763
function correlate(frame1,frame2)

	framesize=rows(frame1);	

	tmp1=10*(ones(rows(frame1)*2,columns(frame1)*2));
	tmp1(1:rows(frame1),1:columns(frame1))=frame1;
	correlation1=xcorr2(tmp1,frame2,"coeff");

	tmp2=10*(ones(rows(frame2)*2,columns(frame2)*2));
	tmp2(1:rows(frame2),1:columns(frame2))=frame2;
	correlation2=xcorr2(tmp2,frame1,"coeff");

	[x1 y1]=findmax(correlation1);
	approx1=frame1(1:x1-framesize/2,1:y1-framesize/2);

	[x2 y2]=findmax(correlation2);
	approx2=frame2(1:x2-framesize/2,1:y2-framesize/2);

	if(size(approx1)==size(approx2))
		system("rm -rf redundant; mkdir redundant");
		imwrite(tmp1,"redundant.png");
	else
		correlate(tmp1,tmp2);
		endif
	end

%%Chris Mullen 10387763
function [x y]=findmax(im)
	[maxval]=max(im(:));
	[x y]=ind2sub(size(im),find(im==maxval));
	end
