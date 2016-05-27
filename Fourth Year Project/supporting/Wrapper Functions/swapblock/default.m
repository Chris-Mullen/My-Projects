%% This function creates a frame and calls my swapblock function twice, once to represent encoding, 
%% and once to represent decoding.
%% Three images will be output: the original frame ("Before.png"), The encoded state ("Intermediate.png")
%% And The decoded state ("After.png"). (Before and after should be the same image)

%% Note: Overlapping blocks have been chosen specifically as a worst case scenario for data loss/duplication
%% Check that "Before" and "After" are equal

%%Chris Mullen 10387763
function default
	%%Create Frame
	back=rand(100,100);
	block1=zeros(20,40);
	blockrows1=rows(block1);
	blockcols1=columns(block1);
	block2=ones(40,20);%%to show that the blocks are being shifted (this will only be part of the frame, not passed in as an argument, but if successful, the white and black blocks should be swapped)
	blockrows2=rows(block2);
	blockcols2=columns(block2);
	frame=back;

	p1={15,20};%%initial point of block (this will be taken from my correlation function)
	p2={20,25};%%destination point of block (this will be taken from my correlation function)

	system("rm -rf reference; mkdir reference");
	cd reference;
		save p1.mat p1;
		save p2.mat p2;
		cd ../

	frame(p1{1}:p1{1}+blockrows1-1,p1{2}:p1{2}+blockcols1-1)=block1;
	frame(p2{1}:p2{1}+blockrows2-1,p2{2}:p2{2}+blockcols2-1)=block2;
	imwrite(frame,"Before.png");
	%%Encode
	frame=swapblock(frame,p1,p2,blockrows1,blockcols1);
	imwrite(frame,"Intermediate.png");

	p1=0;p2=0;%%delete old points to ensure they are read from file
	%%Decode
	cd reference;
		load p1.mat p1;
		load p2.mat p2;
		cd ../
	frame=swapblock(frame,p2,p1,blockrows1,blockcols1);
	imwrite(frame,"After.png");
	end

