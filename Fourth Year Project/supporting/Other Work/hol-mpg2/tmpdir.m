%this function removes the "tmp" directory and everything in it (if it exists) and creates a new one
%used for storing each frame (png) to convert to mpg
function tmpdir
	system("rm -rf tmp; mkdir tmp");
	end
