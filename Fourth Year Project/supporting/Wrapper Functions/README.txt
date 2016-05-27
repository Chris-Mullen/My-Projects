Chris Mullen 10387763

The order of the wrapper from compression to decompression goes as follows:

(compression)
1) findblock_1/findblock_2		(depending on time constraints, findblock_1 is faster but less detailed)
2) swapblock						(first time, to remove motion estimation from the equation, by shifting the redundancy to the correct location)
3)compress						(create the video)

(decompression)
1) decompress					(extract frames from video)
2) swapblock						(again, to reconstruct original frames)
3) testdiff							(to compare the before and after frames for data loss)