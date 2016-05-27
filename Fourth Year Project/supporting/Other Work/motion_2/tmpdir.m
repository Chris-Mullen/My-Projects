%this function checks if a tmp directory exists and if not, creates one in current directory
function tmpdir
	if(exist("tmp","dir"))
		%tmp directory already exists, do nothing
	else
		mkdir("tmp");
		end
	end
