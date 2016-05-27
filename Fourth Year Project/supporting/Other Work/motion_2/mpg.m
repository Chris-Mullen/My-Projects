function mpg
	system("rm -rf mpg-out; mkdir mpg-out");
	%test1
	system("ffmpeg -f image2 -i test1/frame%d.png  mpg-out/test1.mpg ");
	system("ffmpeg -i mpg-out/test1.mpg -vf \"setpts=20.0*PTS\" mpg-out/test1_20.mpg");
	%test2
	system("ffmpeg -f image2 -i test2/frame%d.png -vf \"transpose=2,transpose=2\" -crf 0 test2/frame%d.png");
	system("ffmpeg -f image2 -i test2/frame%d.png -vf \"transpose=2,transpose=2\" mpg-out/test2.mpg ");
	system("ffmpeg -i mpg-out/test2.mpg -vf \"setpts=20.0*PTS\" mpg-out/test2_20.mpg");
	%system("ffmpeg -f image2 -i myimg%d.jpg tmp/mov.mpg");
	%-fv "setpts=5.0*PTS"
	%ffmpeg -i mymovin.mpg -filter:v "setpts=2.0*PTS" mymovout.mpg
	end

