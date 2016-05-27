function openfile(filename)
    	disp(filename);printf("\n");
    	img=imread(filename);
    	%img=pad(img);
	%imwrite(img,"out.png");
	for count = 1:10 % will loop 10 times flipping every second row of every second frame
		img=fliprows(img);
		imwrite(img,sprintf('img%d.png',count),8);
		endfor
	end
