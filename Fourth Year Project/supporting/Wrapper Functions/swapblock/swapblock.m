%%Chris Mullen 10387763
%% This function takes in a frame, two points, and block dimensions; 
%% and swaps the two areas based on these figures.
%% One of the areas is flipped 180 degrees to prevent data loss/duplication
%% It has been made as general as possible so it can be used for both encoding and decoding hologram phase data

%%Chris Mullen 10387763
function frame=swapblock(frame,p1,p2,blockrows,blockcols)
	tmpframe=frame;
	frame(p1{1}:p1{1}+blockrows-1,p1{2}:p1{2}+blockcols-1)=rot90(rot90(tmpframe(p2{1}:p2{1}+blockrows-1,p2{2}:p2{2}+blockcols-1)));
	frame(p2{1}:p2{1}+blockrows-1,p2{2}:p2{2}+blockcols-1)=tmpframe(p1{1}:p1{1}+blockrows-1,p1{2}:p1{2}+blockcols-1);
	end

