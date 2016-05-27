%%the function ofthisfile is to call openfile.m multiple times on different holograms
%%example function call:
%%compress("chip4","0523a","connector2","horse2Manos","Horse2a","LargeScrew","Scr5_03_2k","small_screws","TwoScrews2a","TwoScrewsDepthFar","otter3")
function compress(varargin)%varargin takes in an arbitrary number of arguments
    system("rm -rf holframes; mkdir holframes");
    for count = 1:length(varargin)%length(varargin) is the number of arguments taken in
	%disp(varargin{count});
	openfile(varargin{count},count);
        endfor
        mpg;%convert png's to mpg
    end
