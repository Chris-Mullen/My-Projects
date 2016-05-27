function out=pad(matrix)	
    numrows=rows(matrix);
    numcols=columns(matrix);%length of transpose gives the number of colums
    if(numrows!=numcols)
        if(numrows>numcols)
            out=zeros(numrows);
	    for rowcount=1:numrows
	        for colcount=1:numcols
	    	    out(rowcount,colcount)=out(rowcount,colcount)+matrix(rowcount,colcount);
		    end
		end
	    else
	        out=zeros(numcols);
		for colcount=1:numcols
		    for rowcount=1:numrows
			out(rowcount,colcount)=out(rowcount,colcount)+matrix(rowcount,colcount);
			end
		    end
		end
	else
	    out=matrix;
	    end
	return;
	end
